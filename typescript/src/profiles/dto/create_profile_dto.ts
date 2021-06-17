import { IsAlpha, IsOptional, IsUrl, IsString } from 'class-validator';

export class CreateProfileDto {
    @IsOptional()
    @IsAlpha()
    jobTitle: string;

    @IsOptional()
    @IsUrl()
    photoUrl: string;

    @IsOptional()
    @IsUrl()
    personalWebsite: string;

    @IsOptional()
    @IsString()
    biography: string;
}
