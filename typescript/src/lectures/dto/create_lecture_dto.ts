import { IsAlphanumeric, IsNotEmpty, IsOptional, IsString, IsUrl, Matches } from "class-validator";

export class CreateLectureDto {
    @IsAlphanumeric()
    @Matches(/[A-Za-z]+/)
    title: string;

    @IsString()
    description: string;

    @IsOptional()
    @IsUrl()
    videoUrl: string;
}
