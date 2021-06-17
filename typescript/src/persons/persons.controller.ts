import { Body, Controller, Delete, Get, Param, Patch, Post, Query, UsePipes, ValidationPipe } from '@nestjs/common';
import { CreatePersonDto } from './dto/create_person_dto';
import { Person } from './person.entity';
import { PersonsService } from './persons.service';

@Controller('persons')
export class PersonsController {
    constructor(private readonly personsService : PersonsService) {
        ;
    }

    @UsePipes(new ValidationPipe({ skipMissingProperties: true }))
    @Get ()
    getPersons(@Query() createPersonDto : CreatePersonDto) : Promise<Person[]> {
        return this.personsService.getPersons(createPersonDto);
    }

    @Get ('/:id')
    getPersonById(@Param('id') id: number) : Promise<Person> {
        return this.personsService.getPersonById(id);
    }

    @UsePipes(new ValidationPipe())
    @Post ()
    createPerson(@Body() createPersonDto : CreatePersonDto) : Promise<Person> {
        return this.personsService.createPerson(createPersonDto);
    }

    @Delete ('/:id')
    deletePerson(@Param('id') id :  number) : Promise<void> {
        return this.personsService.deletePerson(id)
    }

    @UsePipes(new ValidationPipe({ skipMissingProperties: true }))
    @Patch ('/:id')
    updatePerson(@Param('id') id : number, @Body() createPersonDto : CreatePersonDto) : Promise<void> {
        return this.personsService.updatePerson(id, createPersonDto);
    }
}
