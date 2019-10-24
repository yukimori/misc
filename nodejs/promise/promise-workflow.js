function asyncFunction() {
	// Promiseオブジェクトを返却する.処理成功時にはresolveが呼ばれる
	return new Promise(function (resolve, reject) {
		setTimeout(function () {
			// 成功
			resolve('Async resolve');
		}, 1000);
	});
}

function asyncFunction_reject() {
	// Promiseオブジェクトを返却する.処理成功時にはresolveが呼ばれる
	return new Promise(function (resolve, reject) {
		setTimeout(function () {
			// 成功
			reject('Async reject');
		}, 2000);
	});
}


asyncFunction().then(function (value) {
	// 非同期処理成功
	console.log(value);    // => 'Async Hello world'
}).catch(function (error) {
	// 非同期処理失敗。呼ばれない
	console.log(error);
});

asyncFunction_reject().then(function (value) {
	// 非同期処理成功
	console.log(value);    // => 'Async Hello world'
}).catch(function (error) {
	// 非同期処理失敗
	console.log(error);
});

setTimeout(function () {
	console.log("alone timeout");
}, 2000);

