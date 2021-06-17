import { NotFoundException } from '@nestjs/common';
import { Common } from 'src/common';
import { EntityRepository, Repository } from 'typeorm';
import { CreateLectureDto } from './dto/create_lecture_dto';
import { Lecture } from './lecture.entity';

@EntityRepository(Lecture)
export class LectureRepository extends Repository<Lecture> {

    async getLectures(createLectureDto : CreateLectureDto) : Promise<Lecture[]> {
        return await this.find(Common.dtoToQryArgs(Lecture.makeFromDto(createLectureDto), createLectureDto));
    }

    async getLectureById(id: string) : Promise<Lecture> {
        const found = await this.findOne((isNaN(Number(id)) ? {slug: id} : {id : id}) as Object);
        if (!found) {
            throw new NotFoundException('lecture not found');
        }
        return found;
    }

    async createLecture(createLectureDto : CreateLectureDto) : Promise<Lecture> {
        const lecture : Lecture = await Lecture.makeFromDto(createLectureDto);
        await lecture.save();
        return lecture;
    }

    async deleteLecture(id: string) : Promise<void> {
        if ((await this.delete((isNaN(Number(id)) ? {slug: id} : {id : id}) as Object)).affected === 0 )
            throw new NotFoundException('lecture not found');
    }

    async updateLecture(id: string, createLectureDto : CreateLectureDto) : Promise<void> {
        if (!createLectureDto || (Object.keys(createLectureDto).length === 0)) return; // nothing to do
        if ((await this.update((isNaN(Number(id)) ? {slug: id} : {id : id}) as Object, Common.dtoToQryArgs(Lecture.makeFromDto(createLectureDto), createLectureDto))).affected === 0)
            throw new NotFoundException('lecture not found');
    }
}
