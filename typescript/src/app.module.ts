import { Module } from '@nestjs/common';
import { CoursesModule } from './courses/courses.module';
import { LecturesModule } from './lectures/lectures.module';
import { ProfilesModule } from './profiles/profiles.module';
import { PersonsModule } from './persons/persons.module';
import { TypeOrmModule } from '@nestjs/typeorm';
import { typeOrmConfig } from './config/typeorm.config';
import { RanksGuard } from './auth/ranks.guard';
import { APP_GUARD } from '@nestjs/core';

@Module({
  imports: [
    TypeOrmModule.forRoot(typeOrmConfig),
    CoursesModule, LecturesModule, ProfilesModule, PersonsModule],
  controllers: [],
  providers: [
    {
      provide: APP_GUARD,
      useClass: RanksGuard,
    }
  ],
})
export class AppModule {}
