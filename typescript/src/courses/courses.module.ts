import { Module } from '@nestjs/common';
import { CoursesController } from './courses.controller';
import { CoursesService } from './courses.service';
import { PersonsModule } from '../persons/persons.module';
import { CourseRepository } from './course.repository';
import { TypeOrmModule } from '@nestjs/typeorm';

@Module({
  controllers: [CoursesController],
  providers: [CoursesService],
  imports: [PersonsModule, TypeOrmModule.forFeature([CourseRepository])]
})
export class CoursesModule {}
