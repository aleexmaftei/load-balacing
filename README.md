## Load balancing timings on C#, Java and Python

#### CPU: Ryzen-7 3700x 3.6GHz
#### RAM: 16GB DDR4 3600MHz CL16 Dual Channe
#### Data: 1000 values as test data

|Algorithm  	| C#         	| Java    	| Python    	|
|---------------------------------------	|------------	|---------	|-----------	|
| FCFS                                  	| 0.0020828s 	| 0.01s   	| 0.035002s 	|
| SJF (Pre-emptive)                     	| 0.1245820s 	| 0.073s  	| 0.170095s 	|
| SJF (Non Pre-emptive)                 	| 0.0296144s 	| 0.016s  	| 0.082018s 	|
| Priority Scheduling (Pre-emptive)     	| 0.1367484s 	| 0.5777s 	| 4.367740s 	|
| Priority Scheduling (Non Pre-emptive) 	| 0.0294884s 	| 0.333s  	| 1.110080s 	|
| Round Robin (Q = 100)                 	| 0.0010806s 	| 0.003s  	| 0.010009s 	|