import { BaseEntity, Column, Entity, PrimaryGeneratedColumn } from "typeorm";
import { CreateProfileDto } from "./dto/create_profile_dto";

@Entity()
export class Profile extends BaseEntity {
    @PrimaryGeneratedColumn()
    id: number;

    @Column({nullable: true})
    photoUrl: string | null;

    @Column({nullable: true})
    jobTitle: string | null;

    @Column({nullable: true})
    personalWebsite: string | null;

    @Column({nullable: true})
    biography: string | null;

    static makeFromDto(createProfileDto: CreateProfileDto) : Profile {
        const profile : Profile = new Profile();
        profile.jobTitle = ('jobTitle' in createProfileDto) ? createProfileDto['jobTitle'] : null;
        profile.photoUrl = ('photoUrl' in createProfileDto) ? createProfileDto['photoUrl'] : null;
        profile.personalWebsite = ('personalWebsite' in createProfileDto) ? createProfileDto['personalWebsite'] : null;
        profile.biography = ('biography' in createProfileDto) ? createProfileDto['biography'] : null;

        return profile;
    }
};
