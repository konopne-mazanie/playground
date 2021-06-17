import { NotFoundException } from "@nestjs/common";
import { Common } from "src/common";
import { EntityRepository, Repository } from "typeorm";
import { CreateProfileDto } from "./dto/create_profile_dto";
import { Profile } from "./profile.entity";

@EntityRepository(Profile)
export class ProfileRepository extends Repository<Profile> {

    async getProfiles(createProfileDto: CreateProfileDto) : Promise<Profile[]> {
        return await this.find(Common.dtoToQryArgs(await Profile.makeFromDto(createProfileDto), createProfileDto));
    }

    async getProfileById(id: number) : Promise<Profile> {
        const found = await this.findOne(id);
        if (!found) {
            throw new NotFoundException('profile not found');
        }
        return found;
    }

    async createProfile(createProfileDto: CreateProfileDto) : Promise<Profile> {
        const profile : Profile = Profile.makeFromDto(createProfileDto);
        await profile.save();
        return profile;
    }

    async deleteProfile(id: number) : Promise<void> {
        if ((await this.delete(id)).affected === 0 )
            throw new NotFoundException('profile not found');
    }

    async updateProfile(id: number, createProfileDto : CreateProfileDto) : Promise<void> {
        if (!createProfileDto || (Object.keys(createProfileDto).length === 0)) return; // nothing to do
        if ((await this.update(id, Common.dtoToQryArgs(await Profile.makeFromDto(createProfileDto), createProfileDto))).affected === 0)
            throw new NotFoundException('profile not found');
    }
};