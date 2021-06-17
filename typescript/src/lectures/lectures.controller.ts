import { Body, Controller, Delete, Get, Param, Patch, Post, Query, UsePipes, ValidationPipe } from '@nestjs/common';
import { Ranks } from 'src/auth/ranks.decorator';
import { PersonRank } from 'src/persons/person-rank.enum';
import { CreateLectureDto } from './dto/create_lecture_dto';
import { Lecture } from './lecture.entity';
import { LecturesService } from './lectures.service';

@Controller('lectures')
export class LecturesController {

    constructor(private readonly lecturesService : LecturesService) {
        ;
    }

    @UsePipes(new ValidationPipe({ skipMissingProperties: true }))
    @Get ()
    getLectures(@Query() createLectureDto : CreateLectureDto) : Promise<Lecture[]> {
        return this.lecturesService.getLectures(createLectureDto);
    }

    // 'id' param always can be slug
    @Get ('/:id')
    getLectureById(@Param('id') id : string) : Promise<Lecture> {
        return this.lecturesService.getLectureById(id);
    }

    @Ranks(PersonRank.TEACHER)
    @UsePipes(new ValidationPipe())
    @Post ()
    createLecture(@Body() createLectureDto : CreateLectureDto) : Promise<Lecture> {
        return this.lecturesService.createLecture(createLectureDto);
    }

    @Ranks(PersonRank.TEACHER)
    @Delete ('/:id')
    deleteLecture(@Param('id') id : string) : Promise<void> {
        return this.lecturesService.deleteLecture(id);
    }

    @Ranks(PersonRank.TEACHER)
    @UsePipes(new ValidationPipe({ skipMissingProperties: true }))
    @Patch ('/:id')
    updateLecture(@Param('id') id : string, @Body() createLectureDto : CreateLectureDto) {
        return this.lecturesService.updateLecture(id, createLectureDto);
    }
}
