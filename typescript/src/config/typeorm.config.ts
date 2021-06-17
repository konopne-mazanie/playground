import { TypeOrmModuleOptions } from "@nestjs/typeorm";

export const typeOrmConfig: TypeOrmModuleOptions = {
    type: 'postgres',
    host: 'localhost',
    port: 5432,
    username: 'postgres',
    password: 'postgres',
    database: 'course_app',
    autoLoadEntities: true,
    synchronize: true,
    entities: ["dist/**/*.entity.js"]
};
