import { Body, Controller, Delete, Get, Param, Patch, Post, Query, UsePipes, ValidationPipe } from '@nestjs/common';
import { Ranks } from 'src/auth/ranks.decorator';
import { PersonRank } from 'src/persons/person-rank.enum';
import { Course } from './course.entity';
import { CoursesService } from './courses.service';
import { CreateCourseDto } from './dto/create_course_dto';

@Controller('courses')
export class CoursesController {
    constructor(private readonly coursesService : CoursesService) {
        ;
    }

    @UsePipes(new ValidationPipe({ skipMissingProperties: true }))
    @Get ()
    getCourses(@Query() createCourseDto : CreateCourseDto) : Promise<Course[]> {
        return this.coursesService.getCourses(createCourseDto);
    }

    // 'id' param always can be slug
    @Get ('/:id')
    getCourseById(@Param('id') id: string) {
        return this.coursesService.getCourseById(id);
    }

    @Ranks(PersonRank.TEACHER)
    @UsePipes(new ValidationPipe())
    @Post ()
    createCourse(@Body() createCourseDto : CreateCourseDto) {
        return this.coursesService.createCourse(createCourseDto);
    }

    @Ranks(PersonRank.TEACHER)
    @Delete ('/:id')
    deleteCourse(@Param('id') id: string) {
        return this.coursesService.deleteCourse(id);
    }

    @Ranks(PersonRank.TEACHER)
    @UsePipes(new ValidationPipe({ skipMissingProperties: true }))
    @Patch ('/:id')
    updateCourse(@Param('id') id: string, @Body() createCourseDto : CreateCourseDto) {
        return this.coursesService.updateCourse(id, createCourseDto);
    }

    @Ranks(PersonRank.TEACHER)
    @Post ('/:id/student/:studentId')
    addStudent(@Param('id') id: string, @Param('studentId') studentId : number) : Promise<void> {
        return this.coursesService.addStudent(id, studentId);
    }

    @Ranks(PersonRank.TEACHER)
    @Post ('/:id/lecture/:lectureId')
    addLecture(@Param('id') id: string, @Param('lectureId') lectureId : number) : Promise<void> {
        return this.coursesService.addLecture(id, lectureId);
    }

    @Ranks(PersonRank.TEACHER)
    @Delete ('/:id/student/:studentId')
    deleteStudent(@Param('id') id: string, @Param('studentId') studentId : number) : Promise<void> {
        return this.coursesService.deleteStudent(id, studentId);
    }

    @Ranks(PersonRank.TEACHER)
    @Delete ('/:id/lecture/:lectureId')
    deleteLecture(@Param('id') id: string, @Param('lectureId') lectureId : number) : Promise<void> {
        return this.coursesService.deleteLecture(id, lectureId);
    }

}
