# node-ucccccp
Universal Cool Cheater Crypto Chit-Chat Protocol Node Module

# Usage
```js
const ucccccp = require('node-ucccccp');
var input = "Hello World!";

var encrypted = ucccccp.encrypt(input);
var decrypted = ucccccp.decrypt(encrypted);

console.log("Encrypted: ", encrypted);
console.log("Decrypted: ", decrypted);
```
