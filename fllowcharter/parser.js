//import * as b from "blocks.js";
let code = `
    #include <iostream>
    using namespace std;

    int main() 
    {
        int a, b;
        cin >> a >> b;
        if(a > b) 
        {
            cout << a << endl;
        } 
        if(a<b)
        {
            cout << b << endl;
            int i = 0;
            while(i < 10) 
            {
                cout << i << endl;
                i++;
            }
        }
        while(a < b) 
        {
            cout << a << endl;
            a++;
        }
        return 0;
    }
`;
let split = code.split("\n");
let openfigbr = 0;
let closefigbr = 0;
let openbr = 0;
let closebr = 0;
let mainmatch = false;

let tree = [];
let currblock = null;
let stack = [];
for (let line of split) {
    //console.log(line)
    codeblock = line.match(/.*(\s\w*\(.*\))/);
    if (codeblock) {
        //console.log(codeblock[1]);
        currblock = codeblock[1];
    }

    if (currblock) {
        if (line.indexOf("{") > -1) {
            //console.log("openfigbr");
            openfigbr++;
            stack.push(currblock);

            let str = stack.length + currblock;
            console.log(str);
        }
        if (line.indexOf("}") > -1) {
            // console.log("close");
            closefigbr++;
            let b = stack.pop();
        }
        if (line.indexOf("cout") > -1) {
            console.log(line);
        }
    }
}
/*
[
    {
        text:main,
        type: function,
        children: [
            {
                text: "int a,b",
                type: code
            },
            {
                text: "a,b",
                type: io
            },
            {
                text: "a>b",
                type: if,
                children:[
                    
                ]
            }
    }
]
*/