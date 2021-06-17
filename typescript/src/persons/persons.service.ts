import { HttpException, HttpStatus, Inject, Injectable } from '@nestjs/common';
import { CreatePersonDto } from './dto/create_person_dto';
import { Person } from './person.entity';
import { ProfilesService } from '../profiles/profiles.service';
import { PersonRepository } from './person.repository';
import { InjectRepository } from '@nestjs/typeorm';
import { QueryFailedError } from 'typeorm';

@Injectable()
export class PersonsService {
    constructor(
        @Inject(ProfilesService) private readonly profilesService : ProfilesService,
        @InjectRepository(PersonRepository) private readonly personRepository: PersonRepository
    ) {}

    async getPersons(createPersonDto : CreatePersonDto) : Promise<Person[]> {
        return this.personRepository.getPersons(createPersonDto, this.profilesService);
    }

    async getPersonById(id: number) : Promise<Person> {
        return this.personRepository.getPersonById(id);
    }

    async createPerson(createPersonDto : CreatePersonDto) : Promise<Person> {
        return this.personRepository.createPerson(createPersonDto, this.profilesService);
    }

    async deletePerson(id: number) : Promise<void> {
        try {
            return await this.personRepository.deletePerson(id);
        } catch (ex) {
            if ((ex instanceof QueryFailedError) && (ex.message.indexOf('foreign key') !== -1))
                throw new HttpException('Person is bound to some course, please update course first!', HttpStatus.CONFLICT);
            else throw ex;
        }
    }

    async updatePerson(id: number, createPersonDto : CreatePersonDto) : Promise<void> {
        return this.personRepository.updatePerson(id, createPersonDto, this.profilesService);
    }
}
