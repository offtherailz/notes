# Notes from Crockford's videos

## Varia

+ `delete` for arrays doesn't do what you expect. It sets the item to `undefined` but doesn't rework the indices of the array. For that use `splice`:

    var array = [1,2,3,4];
    delete array[1];
    // array is now [1, undefined, 3, 4]
    array.splice(1,1);
    // array is now [1,3,4]
