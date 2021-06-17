import { IsAlpha, IsEmail, IsEnum, IsOptional, Matches } from "class-validator";
import { profile } from "node:console";
import { PersonRank } from '../person-rank.enum';

export class CreatePersonDto {
    @IsAlpha()
    firstName: string;

    @IsAlpha()
    lastName: string;

    @IsEmail()
    email: string;

    @IsOptional()
    @Matches(/[0-9]+/)
    profile: number;

    @IsEnum(PersonRank)
    rank : PersonRank;
}
