import { NotFoundException } from '@nestjs/common';
import { Common } from 'src/common';
import { PersonsService } from 'src/persons/persons.service';
import { EntityRepository, Repository } from 'typeorm';
import { Course } from './course.entity';
import { CreateCourseDto } from './dto/create_course_dto';

@EntityRepository(Course)
export class CourseRepository extends Repository<Course> {

    async getCourses(createCourseDto : CreateCourseDto, personsService : PersonsService) : Promise<Course[]> {
        let ret : Course[] = await this.find(Common.dtoToQryArgs(await Course.makeFromDto(createCourseDto, personsService), createCourseDto));
        // lazy relations
        for (let course  of ret) {
            course.lectures = Promise.resolve(await course.lectures);
            course.students = Promise.resolve(await course.students);
            course.teacher = Promise.resolve(await course.teacher);
        }
        return ret;
    }

    async getCourseById(id: string) : Promise<Course> {
        const found = await this.findOne((isNaN(Number(id)) ? {slug: id} : {id : id}) as Object);
        if (!found) {
            throw new NotFoundException('course not found');
        }
        found.lectures = Promise.resolve(await found.lectures);
        found.students = Promise.resolve(await found.students);
        found.teacher = Promise.resolve(await found.teacher);
        return found;
    }

    async createCourse(createCourseDto : CreateCourseDto, personsService : PersonsService) : Promise<Course> {
        const course : Course = await Course.makeFromDto(createCourseDto, personsService);
        await course.save();
        return course;
    }

    async deleteCourse(id: string) : Promise<void> {
        if ((await this.delete((isNaN(Number(id)) ? {slug: id} : {id : id}) as Object)).affected === 0 )
            throw new NotFoundException('course not found');
    }

    async updateCourse(id: string, createCourseDto : CreateCourseDto, personsService : PersonsService) : Promise<void> {
        if (!createCourseDto || (Object.keys(createCourseDto).length === 0)) return; // nothing to do
        const course : Course = await this.getCourseById(id);
        const newCourse = Object.assign(course, Common.dtoToQryArgs(await Course.makeFromDto(createCourseDto, personsService), createCourseDto));
        if (('teacher' in createCourseDto) && !createCourseDto['teacher']) newCourse.teacher = Promise.resolve(null);
        
        await newCourse.save();
    }

    async addStudent(id: string, studentId : number) : Promise<void> {
        const courseIdentifier = await this.getCourseIdentifier(id);
        await this
            .createQueryBuilder()
            .relation(Course, 'students')
            .of(courseIdentifier)
            .add(studentId);
        this.lastUpdatedInc(courseIdentifier);
    }

    async deleteStudent(id: string, studentId : number) : Promise<void> {
        const courseIdentifier = await this.getCourseIdentifier(id);

        if (!(await this.query('SELECT EXISTS(SELECT * FROM course_students_person WHERE "courseId"=$1 AND "personId"=$2);', [courseIdentifier, studentId]))[0]['exists'])
            throw('not found');

        await this
            .createQueryBuilder()
            .relation(Course, 'students')
            .of(courseIdentifier)
            .remove(studentId);
        this.lastUpdatedInc(courseIdentifier);
    }

    async addLecture(id: string, lectureId : number) : Promise<void> {
        const courseIdentifier = await this.getCourseIdentifier(id);
        await this
            .createQueryBuilder()
            .relation(Course, 'lectures')
            .of(courseIdentifier)
            .add(lectureId);
        this.lastUpdatedInc(courseIdentifier);
    }

    async deleteLecture(id: string, lectureId : number) : Promise<void> {
        const courseIdentifier = await this.getCourseIdentifier(id);
        
        if (!(await this.query('SELECT EXISTS(SELECT * FROM course_lectures_lecture WHERE "courseId"=$1 AND "lectureId"=$2);', [courseIdentifier, lectureId]))[0]['exists'])
            throw('not found');
    
        await this
            .createQueryBuilder()
            .relation(Course, 'lectures')
            .of(courseIdentifier)
            .remove(lectureId);
        this.lastUpdatedInc(courseIdentifier);
    }

    private async lastUpdatedInc(id: number) {
        await this.update(id, {lastUpdated: new Date()});
    }

    private async getCourseIdentifier(id: string) : Promise<number> {
        return isNaN(Number(id)) ? (await this.getCourseById(id)).id : id as unknown as number;
    }
}
