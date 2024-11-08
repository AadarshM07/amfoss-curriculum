## Documentation of the Assignment

### **1.data types**


```const items = {};```

- This variable is declared to store a distionary of items that is to be displayed in the website .Here const is used as the details are not going to be reassigned

```const features= {};```

- This variable is declared to store a dictionary of items that contains details regarding all the functionalities of the 

```let shoppingCart = [];```

- This variable is declared to store the list of user selected items further to buy.

```const totalElement=6;```
 
- This variable is declared to store the count of items user has in their cart.It can be displayed while placing order.

```const input="";```

- This variable is to store string.it will be useful to store the users command . which can be further analysed to respond with proper functions.


```const imageElement;```

- This variable will be useful inorder to store any image elemts that need to be displayed regarding the products

```const Discount;```

- This variable will be useful to store if any discounted price is there

```var tax;```

- This variable will be useful to specify tax rate for products

```const actualprice;```

- This variable will be useful inorder to store the actual price and later can be displayed too.

```const icon;```

- This variable will be useful to store any icons if needed

```var final_price;```

- This variable is to calculate and store the final price of the product after tax and discount

```let Bool = true```

- This varibale will be useful to decide whether the payment was succesful or not.



### **2.functions-methods**

```
function function1(name,age){
    var year = 2024-age;
    console.log(`Hello ${name}, you were born in ${year}!`);
}


function1("Aadarsh","17");

Hello Aadarsh, you were born in 2007!


function function2(name, age) {
    var year = 2024 - age;
    const message = `Hello ${name}, you were born in ${year}!`;
    return message;
}

const find = function2("Aadarsh", 17);
console.log(find);
Hello Aadarsh, you were born in 2007!


function multiply(a,b,c){
    const prod=a*b*c;
    return prod;
}
const value=multiply(2,20,30);
console.log(value);

1200

function multiply(a,b=10,c=20){
    const prod=a*b*c;
    return prod;
}
const value=multiply(2);
console.log(value);

400

```


