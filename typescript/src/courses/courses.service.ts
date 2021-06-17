import { HttpException, HttpStatus, Inject, Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { PersonsService } from 'src/persons/persons.service';
import { QueryFailedError } from 'typeorm';
import { Course } from './course.entity';
import { CourseRepository } from './course.repository';
import { CreateCourseDto } from './dto/create_course_dto';

@Injectable()
export class CoursesService {

    constructor(
        @Inject(PersonsService) private readonly personsService : PersonsService,
        @InjectRepository(CourseRepository) private readonly courseRepository: CourseRepository
    ) {}

    async getCourses(createCourseDto : CreateCourseDto) : Promise<Course[]> {
        return this.courseRepository.getCourses(createCourseDto, this.personsService);
    }

    async getCourseById(id: string) : Promise<Course> {
        return this.courseRepository.getCourseById(id);
    }

    async createCourse(createCourseDto : CreateCourseDto) : Promise<Course> {
        try {
            return await this.courseRepository.createCourse(createCourseDto, this.personsService)
        } catch (ex) {
            if ((ex instanceof QueryFailedError) && (ex.message.indexOf('unique constraint') !== -1))
                throw new HttpException('Course with this title already exists!', HttpStatus.CONFLICT);
            else throw ex;
        }
    }

    async deleteCourse(id: string) : Promise<void> {
        return this.courseRepository.deleteCourse(id);
    }

    async updateCourse(id: string, createCourseDto : CreateCourseDto) : Promise<void> {
        return this.courseRepository.updateCourse(id, createCourseDto, this.personsService);
    }

    async addStudent(id: string, studentId : number) : Promise<void> {
        try {
            return await this.courseRepository.addStudent(id, studentId);
        } catch (ex) {
            throw new HttpException('Wrong course or student id!', HttpStatus.NOT_FOUND);
        }
    }

    async deleteStudent(id: string, studentId : number) : Promise<void> {
        try {
            return await this.courseRepository.deleteStudent(id, studentId);
        } catch (ex) {
            throw new HttpException('Wrong course or student id!', HttpStatus.NOT_FOUND);
        }
    }

    async addLecture(id: string, lectureId : number) : Promise<void> {
        try {
            return await this.courseRepository.addLecture(id, lectureId);
        } catch (ex) {
            throw new HttpException('Wrong course or lecture id!', HttpStatus.NOT_FOUND);
        }
    }

    async deleteLecture(id: string, lectureId : number) : Promise<void> {
        try {
            return await this.courseRepository.deleteLecture(id, lectureId);
        } catch (ex) {
            throw new HttpException('Wrong course or lecture id!', HttpStatus.NOT_FOUND);
        }
    }
}
