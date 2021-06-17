import { IsAlphanumeric, isEmpty, IsOptional, IsString, Matches } from "class-validator";

export class CreateCourseDto {
    @IsAlphanumeric()
    @Matches(/[A-Za-z]+/)
    title: string;

    @IsString()
    description: string;

    @IsOptional()
    @Matches(/^[0-9]*$/)
    teacher: number;
}
