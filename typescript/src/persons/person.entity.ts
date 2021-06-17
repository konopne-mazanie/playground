import { Profile } from "src/profiles/profile.entity";
import { BaseEntity, Column, Entity, JoinColumn, OneToOne, PrimaryGeneratedColumn } from "typeorm";
import { PersonRank } from './person-rank.enum';
import { CreatePersonDto } from './dto/create_person_dto';
import { ProfilesService } from '../profiles/profiles.service';
import { Course } from "src/courses/course.entity";

@Entity()
export class Person extends BaseEntity {
    @PrimaryGeneratedColumn()
    id: number;

    @Column()
    firstName: string;

    @Column()
    lastName: string;

    @Column()
    email: string;

    @OneToOne(() => Profile)
    @JoinColumn()
    profile: Promise<Profile>;

    @Column()
    rank: PersonRank;

    courses : Course[];

    static async makeFromDto(createPersonDto : CreatePersonDto, profilesService : ProfilesService) : Promise<Person> {
        const person : Person = new Person();
        person.firstName = ('firstName' in createPersonDto) ? createPersonDto['firstName'] : null;
        person.lastName = ('lastName' in createPersonDto) ? createPersonDto['lastName'] : null;
        person.email = ('email' in createPersonDto) ? createPersonDto['email'] : null;
        person.profile = Promise.resolve(('profile' in createPersonDto) ? await profilesService.getProfileById(createPersonDto['profile']) : null);
        
        person.rank = ('rank' in createPersonDto) ? createPersonDto['rank'] : null;

        return person;
    }
}
