false;
true;
undefined;

// Inaccessible in ES
class Primitive {
    str(): string {}
    bool(): bool {}
    typeOf(): string {}
    hasProperty(key: string): bool {}
    __getProperty__(key: any): any {}
    clone(): any {}

    // Optional - might be undefined
    __add__(n: any): any;
    __subtract__(n: any): any;
    __multiply__(n: any): any;
    __divide__(n: any): any;
    __pow__(n: any): any;
    __eq__(n: any): any;
    __gt__(n: any): any;
    __lt__(n: any): any;
    __and__(n: any): any;
    __or__(n: any): any;
    __bool__(): boolean | Error;
    __setProperty__(key: any, value: any): Error | undefined;
    __getProperty__(key: any) => any;
    __call__(parameters: any[], context: any): Error | any;
}

class type extends Primitive<undefined> {
    __isPrimitive__: bool;
    __name__: string;
    __extends__: Type | undefined;
    __methods__: Function[];
    __init__: Function  undefined;
    __instances__: Object[];

    includesType (t: Type): bool {}
    equals (t: Type): bool {}
}

class number extends Primitive<number> {

}

class string extends Primitive<string> {
    len(): number {}
}

class undefined extends Primitive<undefined> {

}

class error extends Primitive<any> {

}

class function extends Primitive<any> {
    name: string;
    arguments_: any[];
    this_: any;
    returnType: Type;
}

class bool extends Primitive {

}

class object extends Primitive {

}

class array extends Primitive {
    len: number;
    add(val: any, idx: number=(len-1))
}

range (n: number): number[] {}
log(msg: any): undefined {};
parseNum(str: any): number | error {};
import(url: string): undefined {};
print(msg: any): undefined {};
input(msg: string, cb: function): string {};