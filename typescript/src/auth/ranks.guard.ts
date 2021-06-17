import { Injectable, CanActivate, ExecutionContext, Inject } from '@nestjs/common';
import { Reflector } from '@nestjs/core';
import { PersonRank } from 'src/persons/person-rank.enum';
import { Person } from 'src/persons/person.entity';
import { PersonsService } from 'src/persons/persons.service';
import { RANKS_KEY } from './ranks.decorator';

@Injectable()
export class RanksGuard implements CanActivate {
  constructor(
    @Inject(PersonsService) private readonly personsService : PersonsService,
    private reflector: Reflector
  ) {}

  async canActivate(context: ExecutionContext): Promise<boolean> {
    const possibleRanks = this.reflector.getAllAndOverride<PersonRank[]>(RANKS_KEY, [
      context.getHandler(),
      context.getClass(),
    ]);
    if (!possibleRanks) return true;

    const personId = context.switchToHttp().getRequest().headers['authid'];
    if (!personId) return false;

    const person : Person = await this.personsService.getPersonById(personId);
    return (person && possibleRanks.includes(person.rank));
  }
}
