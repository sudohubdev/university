//тут знаходяться 'глобальні' функції, які використовуються в різних місцях
//цей код тільки для інтерактивного режиму (не прив'язаний до алгоритмів)
const AsyncFunction = (async function () { }).constructor;
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
    async output(data, chr = '&#62;') {
        let span = document.createElement("span");
        span.innerHTML = `${chr} ${data}`;
        this.parent.appendChild(span);
    }
    async error(data) {
        let span = document.createElement("span");
        span.innerHTML = `&#33; ${data}`;
        this.parent.appendChild(span);
    }
}

class TestIO extends DOMIO {
    constructor(parent, input, btn, stdin) {
        super(parent, input, btn);
        this.in = stdin;
        this._line = 0;
    }
    async input(data) {
        this.output(data);
        this.output("Введено " + this.in[this._line], '&#60;');
        return this.in[this._line++];
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
    async getStdin() {
        let req = await fetch("./" + this.lab + ".json");
        let stdin = JSON.parse(await req.text());
        return stdin;
    }

    async call(IO) {
        var code = await this.getCode();
        //не збити вчителя з пантелику і замаскувати асинхронність
        code = code.replaceAll("input", "await input")
            .replaceAll("output", "await output")
            .replaceAll("error", "await error");
        let lab = this.lab;

        if (IO == null)
            IO = this._io;
        //make IO.input available in the code
        let IOstub = `
            const IO = arguments[0];
            const input = IO.input;
            const output = IO.output;
            const error = IO.error;
        `;
        let func = new AsyncFunction(IOstub + code + "\nawait output('Програма завершила роботу.');");
        await func.call(lab, IO);
    }
    async test() {
        for (let i = 0; i < 2; i++) {
            await this._io.output("Тест " + (i + 1));
            let stdin = await this.getStdin();
            let IO = new TestIO(this._io.parent, this._io.in, this._io.btn, stdin[i]);
            await this.call(IO);
            await this._io.output("&nbsp;", "&nbsp;");
        }
        await this._io.output("Тести завершено.");
    }
}