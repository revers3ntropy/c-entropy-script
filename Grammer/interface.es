false;
true;
undefined;

// Inaccessible in ES
const Primitive = class {
    str(): string {};
    bool(): bool {};
    typeOf(): string {};
    hasProperty(key: string): bool {};
    __getProperty__(key: any): any {};
    clone(): any {};

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
    __getProperty__(key: any): any;
    __call__(parameters: any[], context: any): Error | any;
};

const type = class extends Primitive {
    __isPrimitive__: bool;
    __name__: string;
    __extends__: Type | undefined;
    __methods__: Function[];
    __init__: Function  undefined;
    __instances__: Object[];

    includesType (t: Type): bool {};
    equals (t: Type): bool {};
};

const number = class extends Primitive {

};

const string = class extends Primitive {
    len(): number {}
};

const undefined = class extends Primitive {

};

const error = class extends Primitive<any> {

};

const function = class extends Primitive<any> {
    name: string;
    arguments_: any[];
    this_: any;
    returnType: Type;
};

const bool = class extends Primitive {

};

class object extends Primitive {

};

class array extends Primitive {
    len: number;
    add(val: any, idx: number=(len-1))
};

const range    = func (n: number): number[] {};
const log      = func (msg: any): undefined {};
const parseNum = func (str: any): number | error {};
const import   = func (url: string): undefined {};
const print    = func (msg: any): undefined {};
const input    = func (msg: string, cb: function): string {};