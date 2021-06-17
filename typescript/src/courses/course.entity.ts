import slugify from 'slugify';
import { BaseEntity, Entity, PrimaryGeneratedColumn, Column, ManyToMany, JoinTable, ManyToOne, Unique } from 'typeorm';
import { CreateCourseDto } from './dto/create_course_dto';
import { PersonsService } from '../persons/persons.service';
import { Lecture } from 'src/lectures/lecture.entity';
import { Person } from '../persons/person.entity';
import { PersonRank } from 'src/persons/person-rank.enum';
import { UnauthorizedException } from '@nestjs/common';

@Entity()
@Unique(["title"])
export class Course extends BaseEntity {

    @PrimaryGeneratedColumn()
    id: number;

    @Column()
    title: string;

    @Column()
    slug: string;

    @Column()
    description: string;

    @Column()
    created: Date;

    @Column()
    lastUpdated: Date;

    @ManyToMany(() => Lecture)
    @JoinTable()
    lectures: Promise<Lecture[]>;

    @ManyToMany(() => Person)
    @JoinTable()
    students: Promise<Person[]>;

    @ManyToOne(() => Person, teacher => teacher.courses)
    teacher: Promise<Person>;

    constructor() {
        super();
    }

    static async makeFromDto(createCourseDto : CreateCourseDto, personsService : PersonsService) : Promise<Course> {
        const course = new Course();
        if ('title' in createCourseDto) {
            course.title = createCourseDto['title'];
            course.slug = slugify(course.title);
        } else course.title = null;
        course.description = ('description' in createCourseDto) ? createCourseDto['description'] : null;
        course.created = new Date();
        course.lastUpdated = course.created;
        let person = null;
        if (('teacher' in createCourseDto) && createCourseDto['teacher']) {
            person = await personsService.getPersonById(createCourseDto['teacher']);
            if (person && (person.rank !== PersonRank.TEACHER)) throw new UnauthorizedException('permission denied');
        }
        course.teacher = Promise.resolve(person);

        return course;
    }

}