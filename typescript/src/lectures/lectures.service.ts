import { HttpException, HttpStatus, Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { QueryFailedError } from 'typeorm';
import { CreateLectureDto } from './dto/create_lecture_dto';
import { Lecture } from './lecture.entity';
import { LectureRepository } from './lecture.repository';

@Injectable()
export class LecturesService {

    constructor(
        @InjectRepository(LectureRepository) private readonly lectureRepository : LectureRepository
    ) {}

    async getLectures(createLectureDto : CreateLectureDto) : Promise<Lecture[]> {
        return this.lectureRepository.getLectures(createLectureDto);
    }

    async getLectureById(id: string) : Promise<Lecture> {
        return this.lectureRepository.getLectureById(id);
    }

    async createLecture(createLectureDto : CreateLectureDto) : Promise<Lecture> {
        try {
            return await this.lectureRepository.createLecture(createLectureDto);
        } catch (ex) {
            if ((ex instanceof QueryFailedError) && (ex.message.indexOf('unique constraint') !== -1))
                throw new HttpException('Lexture with this title already exists!', HttpStatus.CONFLICT);
            else throw ex;
        }
    }

    async deleteLecture(id: string) : Promise<void> {
        return this.lectureRepository.deleteLecture(id);
    }

    async updateLecture(id: string, createLectureDto : CreateLectureDto) : Promise<void> {
        return this.lectureRepository.updateLecture(id, createLectureDto);
    }
}
