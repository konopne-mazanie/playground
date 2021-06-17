import { Module } from '@nestjs/common';
import { PersonsService } from './persons.service';
import { PersonsController } from './persons.controller';
import { ProfilesModule } from '../profiles/profiles.module';
import { PersonRepository } from './person.repository';
import { TypeOrmModule } from '@nestjs/typeorm';

@Module({
  providers: [PersonsService],
  controllers: [PersonsController],
  imports: [ProfilesModule, TypeOrmModule.forFeature([PersonRepository])],
  exports: [PersonsService]
})
export class PersonsModule {}
