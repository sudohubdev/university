//тут знаходяться 'глобальні' функції, які використовуються в різних місцях
//цей код тільки для інтерактивного режиму (не прив'язаний до алгоритмів)

class AbstractIO {
    constructor() { }
    async input(data) {
        throw new Error("Not implemented");
    }
    async output(data) {
        throw new Error("Not implemented");
    }
    async error(data) {
        throw new Error("Not implemented");
    }
}

class TextIO extends AbstractIO {
    constructor() {
        super();
    }
    async input(data) {
        return prompt("Введіть дані:\n" + data);
    }
    async output(data) {
        alert("Вивід даних:\n" + data);
    }
    async error(data) {
        alert("Помилка:\n" + data);
    }
}

class DOMIO extends AbstractIO {
    /**
     * 
     * @param { HTMLElement } parent 
     * @param { HTMLElement } btn 
     * @param { HTMLElement } input 
     */
    constructor(parent, input, btn) {
        super();
        this.parent = parent;
        this.btn = btn;
        this.in = input;
        this.output = this.output.bind(this);
        this.input = this.input.bind(this);
    }
    async input(data) {
        this.output(data);
        let promise = new Promise((resolve, reject) => {
            this.btn.onclick = () => {
                let span = document.createElement("span");
                span.innerHTML = `&#60; ${this.in.value}`;
                this.parent.appendChild(span);
                this.btn.onclick = null;
                resolve(this.in.value);
            };
        });
        return promise;
    }
    async output(data) {
        let span = document.createElement("span");
        span.innerHTML = `&#62; ${data}`;
        this.parent.appendChild(span);
    }
}

class LabCaller {
    constructor(lab, io) {
        this._lab = lab;
        this._cachedCode = null;
        this._io = io;
    }
    get lab() {
        return this._lab;
    }
    async getCode() {
        if (!this._cachedCode) {
            let req = await fetch("./" + this.lab + ".js");
            let code = await req.text();
            this._cachedCode = code;
        }
        return this._cachedCode;
    }

    async call() {
        let code = await this.getCode();
        let lab = this.lab;
        let IO = this._io;
        //makke IO.input available in the code
        let IOstub = `
            const IO = arguments[0];
            const input = IO.input;
            const output = IO.output;
            const error = IO.error;
        `;
        let func = new Function(IOstub + code);
        func.call(lab, IO);
    }
}