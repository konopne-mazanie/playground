import { SetMetadata } from '@nestjs/common';
import { PersonRank } from 'src/persons/person-rank.enum';

export const RANKS_KEY = 'ranks';
export const Ranks = (...ranks: PersonRank[]) => SetMetadata(RANKS_KEY, ranks);
