import { HttpException, HttpStatus, Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { QueryFailedError } from 'typeorm';
import { CreateProfileDto } from './dto/create_profile_dto';
import { Profile } from './profile.entity';
import { ProfileRepository } from './profile.repository';

@Injectable()
export class ProfilesService {
    constructor(@InjectRepository(ProfileRepository) private readonly profileRepository: ProfileRepository) {
        ;
    }


    async getProfiles(createProfileDto: CreateProfileDto) : Promise<Profile[]> {
        return this.profileRepository.getProfiles(createProfileDto);
    }

    async getProfileById(id: number) : Promise<Profile> {
        return this.profileRepository.getProfileById(id);
    }

    async createProfile(createProfileDto: CreateProfileDto) : Promise<Profile> {
        return this.profileRepository.createProfile(createProfileDto);
    }

    async deleteProfile(id: number) : Promise<void> {
        try {
            return await this.profileRepository.deleteProfile(id);
        } catch (ex) {
            if ((ex instanceof QueryFailedError) && (ex.message.indexOf('foreign key') !== -1))
                throw new HttpException('Profile is bound to some person, please update person first!', HttpStatus.CONFLICT);
            else throw ex;
        }
    }

    async updateProfile(id: number, createProfileDto : CreateProfileDto) : Promise<void> {
        return this.profileRepository.updateProfile(id, createProfileDto);
    }
    
}
