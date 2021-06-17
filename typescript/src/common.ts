import { BaseEntity } from "typeorm";

export class Common {
    static dtoToQryArgs(entity : BaseEntity, dto : Object) : Object {

        let args = {};

        for (let key in dto) {
            if (!dto[key]) continue;
            args[key] = entity[key];
        }

        return args;
    }
}
