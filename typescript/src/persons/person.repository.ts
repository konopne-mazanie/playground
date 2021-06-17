import { NotFoundException } from "@nestjs/common";
import { EntityRepository, Repository } from "typeorm";
import { CreatePersonDto } from "./dto/create_person_dto";
import { Person } from "./person.entity";
import { ProfilesService } from '../profiles/profiles.service';
import { Common } from '../common';


@EntityRepository(Person)
export class PersonRepository extends Repository<Person> {

    async getPersons(createPersonDto : CreatePersonDto, profilesService : ProfilesService) : Promise<Person[]> {
        let ret : Person[] = await this.find(Common.dtoToQryArgs(await Person.makeFromDto(createPersonDto, profilesService), createPersonDto));
        // lazy relations
        for (let person  of ret) person.profile = Promise.resolve(await person.profile);
        return ret;
    }

    async getPersonById(id: number) : Promise<Person> {
        const found = await this.findOne(id);
        if (!found) {
            throw new NotFoundException('person not found');
        }
        return found;
    }

    async createPerson(createPersonDto : CreatePersonDto, profilesService : ProfilesService) : Promise<Person> {
        const person : Person = await Person.makeFromDto(createPersonDto, profilesService);
        await person.save();
        return person;
    }

    async deletePerson(id: number) : Promise<void> {
        if ((await this.delete(id)).affected === 0 )
            throw new NotFoundException('person not found');
    }

    async updatePerson(id: number, createPersonDto : CreatePersonDto, profilesService : ProfilesService) : Promise<void> {
        if (!createPersonDto || (Object.keys(createPersonDto).length === 0)) return; // nothing to do
        const person : Person = await this.getPersonById(id);
        const newPerson = Object.assign(person, Common.dtoToQryArgs(await Person.makeFromDto(createPersonDto, profilesService), createPersonDto));
        await newPerson.save();
    }
};
