import { Body, Controller, Delete, Get, Param, ParseIntPipe, Patch, Post, Query, UsePipes, ValidationPipe } from '@nestjs/common';
import { CreateProfileDto } from './dto/create_profile_dto';
import { Profile } from './profile.entity';
import { ProfilesService } from './profiles.service';

@Controller('profiles')
export class ProfilesController {

    constructor(private readonly profilesService : ProfilesService) {
        ;
    }

    @Get ()
    getProfiles(@Query() createProfileDto : CreateProfileDto) : Promise<Profile[]> {
        return this.profilesService.getProfiles(createProfileDto);
    }

    @Get ('/:id')
    getProfileById(@Param('id', ParseIntPipe) id: number) : Promise<Profile> {
        return this.profilesService.getProfileById(id);
    }

    @UsePipes(ValidationPipe)
    @Post ()
    createProfile(@Body() createProfileDto : CreateProfileDto) : Promise<Profile> {
        return this.profilesService.createProfile(createProfileDto);
    }

    @Delete ('/:id')
    deleteProfile(@Param('id') id: number) : Promise<void> {
        return this.profilesService.deleteProfile(id);
    }

    @UsePipes(ValidationPipe)
    @Patch ('/:id')
    updateProfile(@Param('id') id: number, @Body() createProfileDto : CreateProfileDto) : Promise<void> {
        return this.profilesService.updateProfile(id, createProfileDto);
    }
}
