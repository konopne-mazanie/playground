import slugify from "slugify";
import { BaseEntity, Column, Entity, ManyToOne, PrimaryGeneratedColumn, Unique } from "typeorm";
import { CreateLectureDto } from "./dto/create_lecture_dto";

@Entity()
@Unique(["title"])
export class Lecture extends BaseEntity {

    @PrimaryGeneratedColumn()
    id: number;

    @Column()
    title: string;

    @Column()
    slug: string;

    @Column()
    description: string;

    @Column()
    videoUrl: string;

    constructor() {
        super();
    }

    static makeFromDto(createLectureDto : CreateLectureDto) : Lecture {
        const lecture : Lecture = new Lecture();
        if ('title' in createLectureDto) {
            lecture.title = createLectureDto['title'];
            lecture.slug = slugify(lecture.title);
        } else lecture.title = null;
        lecture.title = ('title' in createLectureDto) ? createLectureDto['title'] : null;
        lecture.description = ('description' in createLectureDto) ? createLectureDto['description'] : null;
        lecture.videoUrl = ('videoUrl' in createLectureDto) ? createLectureDto['videoUrl'] : null;

        return lecture;
    }
}
