#include<cstdio>
#include<cstdlib>
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<chrono>
#include<iomanip>
#include<algorithm>

using namespace std;

typedef struct proces {
    string nume;
    int timpOcupare;  /// durata procesului
    int timpInceput;  /// cand incepe procesul
    int prioritate;
    int timpAsteptare, timpProcesare;
    int verificat;
} proces;

bool verbose = false;

bool compare(const proces A, const proces B) {
    return A.timpInceput < B.timpInceput;
}

pair<vector<proces>, int> fileRead(string path) {
    string nume, timpOcupare, timpInceput, prioritate, n;

    pair<vector<proces>, int> values;
    ifstream fin(path);
    getline(fin, n, '\n');
    proces arr[stoi(n)];

    while (getline(fin, nume, ',') &&
           getline(fin, timpOcupare, ',') &&
           getline(fin, timpInceput, ',') &&
           getline(fin, prioritate, '\n')) {
        proces p;
        p.nume = nume;
        p.timpOcupare = stoi(timpOcupare);
        p.timpInceput = stoi(timpInceput);
        p.prioritate = stoi(prioritate);
        p.verificat = 0;
        values.first.push_back(p);
    }

    values.second = stoi(n);

    fin.close();
    return values;
}

/// FCFS Algorithm - FIFO (primul venit primul servit), cel mai slab ca timp
void FCFS(vector<proces> P, int n) {
    proces temp[n];
    int sumaTimpAsteptare = 0, sumaTimpProcesare = 0;
    int x = 0;
    float timpMediuAsteptare = 0.0, timpMediuProcesare = 0.0;
    int i, j;

    auto start = chrono::high_resolution_clock::now();

    for (i = 0; i < n; i++)
        temp[i] = P[i];

    sort(temp, temp + (n - 1), compare);

    if (verbose) {
        printf("\n\n PROC.\tB.T.\tA.T.");
        for (i = 0; i < n; i++)
            printf("\n %s\t%d\t%d", temp[i].nume.c_str(), temp[i].timpOcupare, temp[i].timpInceput);
    }
    sumaTimpAsteptare = temp[0].timpAsteptare = 0;
    sumaTimpProcesare = temp[0].timpProcesare = temp[0].timpOcupare - temp[0].timpInceput;

    for (i = 1; i < n; i++) {
        temp[i].timpAsteptare =
                (temp[i - 1].timpOcupare + temp[i - 1].timpInceput + temp[i - 1].timpAsteptare) - temp[i].timpInceput;
        temp[i].timpProcesare = (temp[i].timpAsteptare + temp[i].timpOcupare);
        sumaTimpAsteptare += temp[i].timpAsteptare;
        sumaTimpProcesare += temp[i].timpProcesare;
    }
    timpMediuAsteptare = (float) sumaTimpAsteptare / n;
    timpMediuProcesare = (float) sumaTimpProcesare / n;

    if (verbose) {
        printf("\n\n PROC.\tB.T.\tA.T.\tW.T\tT.A.T");
        for (i = 0; i < n; i++)
            printf("\n %s\t%d\t%d\t%d\t%d", temp[i].nume.c_str(), temp[i].timpOcupare, temp[i].timpInceput, temp[i].timpAsteptare,
                   temp[i].timpProcesare);

        printf("\n\n GANTT CHART\n ");
        for (i = 0; i < n; i++)
            printf("   %s   ", temp[i].nume.c_str());
        printf("\n ");

        printf("0\t");
    }
    for (i = 1; i <= n; i++) {
        x += temp[i - 1].timpOcupare;
        if (verbose)
            printf("%d      ", x);
    }

    auto end = chrono::high_resolution_clock::now();

    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;

    cout << "\nWall clock: " << fixed << time_taken << setprecision(9);
    cout << " sec";

    printf("\n Timpul mediu de asteptare = %0.2f\n Timpul mediu de procesare = %0.2f.\n \n", timpMediuAsteptare,
           timpMediuProcesare);
}

// SJF Non Pre-emptive
void SJF_NP(vector<proces> P, int n) {
    proces temp[n];
    proces t;
    int sumaTimpAsteptare = 0, sumaTimpProcesare = 0;
    int x = 0;
    float timpMediuAsteptare = 0.0, timpMediuProcesare = 0.0;
    int i, j;

    auto start = chrono::high_resolution_clock::now();

    for (i = 0; i < n; i++)
        temp[i] = P[i];

    sort(temp, temp + (n - 1), compare);

    for (i = 2; i < n; i++)
        for (j = 1; j < n - i + 1; j++) {
            if (temp[j].timpOcupare > temp[j + 1].timpOcupare) {
                t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }

    if (verbose) {
        printf("\n\n PROC.\tB.T.\tA.T.");
        for (i = 0; i < n; i++)
            printf("\n %s\t%d\t%d", temp[i].nume.c_str(), temp[i].timpOcupare, temp[i].timpInceput);
    }

    sumaTimpAsteptare = temp[0].timpAsteptare = 0;
    sumaTimpProcesare = temp[0].timpProcesare = temp[0].timpOcupare - temp[0].timpInceput;

    for (i = 1; i < n; i++) {
        temp[i].timpAsteptare =
                (temp[i - 1].timpOcupare + temp[i - 1].timpInceput + temp[i - 1].timpAsteptare) - temp[i].timpInceput;
        temp[i].timpProcesare = (temp[i].timpAsteptare + temp[i].timpOcupare);
        sumaTimpAsteptare += temp[i].timpAsteptare;
        sumaTimpProcesare += temp[i].timpProcesare;
    }

    timpMediuAsteptare = (float) sumaTimpAsteptare / n;
    timpMediuProcesare = (float) sumaTimpProcesare / n;

    if (verbose) {
        printf("\n\n PROC.\tB.T.\tA.T.\tW.T\tT.A.T");
        for (i = 0; i < n; i++)
            printf("\n %s\t%d\t%d\t%d\t%d", temp[i].nume.c_str(), temp[i].timpOcupare, temp[i].timpInceput, temp[i].timpAsteptare,
                   temp[i].timpProcesare);

        printf("\n\n GANTT CHART\n ");
        for (i = 0; i < n; i++)
            printf("   %s   ", temp[i].nume.c_str());
        printf("\n ");

        printf("0\t");
    }
    for (i = 1; i <= n; i++) {
        x += temp[i - 1].timpOcupare;
        if (verbose) { printf("%d      ", x); }
    }
    auto end = chrono::high_resolution_clock::now();

    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;

    cout << "\nWall clock: " << fixed << time_taken << setprecision(9);
    cout << " sec";

    printf("\nTimpul mediu de asteptare = %0.2f\n Timpul mediu de procesare = %0.2f.", timpMediuAsteptare,
           timpMediuProcesare);

}

/// Priority Non Pre-emptive - primul cu prioritatea cea mai mare este luat primul si executat
/// fiecare in ordinea data de prioritate se asteapta pana se termina si dupa trece la urmatorul
void PRT_NP(vector<proces> P, int n) {
    proces temp[n];
    proces t;
    int sumaTimpAsteptare = 0, sumaTimpProcesare = 0;
    float timpMediuAsteptare = 0.0, timpMediuProcesare = 0.0;
    int i, j;
    int x = 0;

    auto start = chrono::high_resolution_clock::now();

    for (i = 0; i < n; i++)
        temp[i] = P[i];

    sort(temp, temp + (n - 1), compare);  /// sortare crescatoare dupa timpul de inceput

    for (i = 2; i < n; i++)  /// sortare crescatoare dupa prioritate
        for (j = 1; j < n - i + 1; j++) {
            if (temp[j].prioritate > temp[j + 1].prioritate) {
                t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }

    if (verbose) {
        printf("\n\n PROC.\tTimp Ocupare\tTimp Inceput");
        for (i = 0; i < n; i++)
            printf("\n %s\t%d\t\t%d", temp[i].nume.c_str(), temp[i].timpOcupare, temp[i].timpInceput);
    }
    sumaTimpAsteptare = temp[0].timpAsteptare = 0;
    sumaTimpProcesare = temp[0].timpProcesare = temp[0].timpOcupare - temp[0].timpInceput;

    for (i = 1; i < n; i++) {
        temp[i].timpAsteptare =
                (temp[i - 1].timpOcupare + temp[i - 1].timpInceput + temp[i - 1].timpAsteptare) - temp[i].timpInceput;
        temp[i].timpProcesare = (temp[i].timpAsteptare + temp[i].timpOcupare);
        sumaTimpAsteptare += temp[i].timpAsteptare;
        sumaTimpProcesare += temp[i].timpProcesare;
    }

    timpMediuAsteptare = (float) sumaTimpAsteptare / n;
    timpMediuProcesare = (float) sumaTimpProcesare / n;

    if (verbose) {
        printf("\n\n PROC.\tTimp Ocupare\tTimp Inceput\tTimp Asteptare\tTimp Procesare");
        for (i = 0; i < n; i++)
            printf("\n %s\t%d\t\t%d\t\t%d\t\t%d", temp[i].nume.c_str(), temp[i].timpOcupare, temp[i].timpInceput,
                   temp[i].timpAsteptare, temp[i].timpProcesare);
    }

    if (verbose) {
        printf("\n\n GANTT CHART\n ");
        for (i = 0; i < n; i++)
            printf("   %s   ", temp[i].nume.c_str());
        printf("\n ");
        printf("0\t");
    }

    for (i = 1; i <= n; i++) {
        x += temp[i - 1].timpOcupare;
        if (verbose) { printf("%d      ", x); }
    }

    auto end = chrono::high_resolution_clock::now();

    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;

    cout << "\nWall clock: " << fixed << time_taken << setprecision(9);
    cout << " sec";

    printf("\n Timpul mediu de asteptare = %0.2f\n Timpul mediu de procesare = %0.2f.\n \n", timpMediuAsteptare,
           timpMediuProcesare);
}

/// Round Robin Scheduling - preentiv - poate fi intrerupt si sa continue mai tarziu in cazul in care a ajuns la quantumul introdus
void RR(vector<proces> P, int n, int Q) {
    int nrProceseVerif = 0, t, timpCurent = 0, k, i;
    int sumaTimpAsteptare = 0, sumaTimpProcesare = 0;
    float timpMediuAsteptare = 0.0, timpMediuProcesare = 0.0;
    proces temp1[n], temp2[n];

    auto start = chrono::high_resolution_clock::now();

    for (i = 0; i < n; i++)
        temp1[i] = P[i];

    sort(temp1, temp1 + (n - 1), compare);  /// sorteaza crescator dupa timpul de inceput

    for (i = 0; i < n; i++)
        temp2[i] = temp1[i];

    for (k = 0;; k++) {
        if (k > n - 1)
            k = 0;

        if (temp1[k].timpOcupare > 0 && verbose)
            printf("(%s  %d)", temp1[k].nume.c_str(), timpCurent);
        // printf("(  %d  %s)", timpCurent, temp1[k].nume);
        t = 0;

        /// ii scade din timpul de ocupare pana in quantum si adauga la cat timp s-a executat
        /// il va relua mai tarziu daca trece de quantum, din nou
        while (t < Q && temp1[k].timpOcupare > 0) {
            t++;
            timpCurent++;
            temp1[k].timpOcupare--;
        }

        /// si-a ocupat deja timpul si il calculam cat i-a luat pana aucm sa il faca
        if (temp1[k].timpOcupare <= 0 && temp1[k].verificat != 1) {
            temp1[k].timpAsteptare = timpCurent - temp2[k].timpOcupare - temp1[k].timpInceput;
            temp1[k].timpProcesare =
                    timpCurent - temp1[k].timpInceput;  /// timpul de cand a inceput si pana s-a terminat
            nrProceseVerif++;
            temp1[k].verificat = 1;
            sumaTimpAsteptare += temp1[k].timpAsteptare;
            sumaTimpProcesare += temp1[k].timpProcesare;
        }

        if (nrProceseVerif == n)
            break;
    }
    auto end = chrono::high_resolution_clock::now();

    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;

    cout << "\nWall clock: " << fixed << time_taken << setprecision(9);
    cout << " sec";

    timpMediuAsteptare = (float) sumaTimpAsteptare / n;
    timpMediuProcesare = (float) sumaTimpProcesare / n;


    printf("\nTimp curent  %d", timpCurent);
    printf("\n Timpul mediu de asteptare = %0.2f\n Timpul mediu de procesare = %0.2f.\n \n", timpMediuAsteptare,
           timpMediuProcesare);

}

// Shortest Job First - Pre-emptive
void SJF_P(vector<proces> P, int n) {
    int i, t_total = 0, timpCurent, b[n], j, x, min_timpOcupare;
    int sumaTimpAsteptare = 0, sumaTimpProcesare = 0;
    float timpMediuAsteptare = 0.0, timpMediuProcesare = 0.0;
    proces temp[n], t;

    auto start = chrono::high_resolution_clock::now();

    for (i = 0; i < n; i++) {
        temp[i] = P[i];
        t_total += P[i].timpOcupare;
    }

    sort(temp, temp + (n - 1), compare);

    for (i = 0; i < n; i++)
        b[i] = temp[i].timpOcupare;

    i = j = 0;
    if (verbose)
        printf("\n GANTT CHART\n\n %d %s", i, temp[i].nume.c_str());

    for (timpCurent = 0; timpCurent < t_total; timpCurent++) {
        if (b[i] > 0 && temp[i].timpInceput <= timpCurent)
            b[i]--;

        if (i != j && verbose)
            printf(" %d %s", timpCurent, temp[i].nume.c_str());

        if (b[i] <= 0 && temp[i].verificat != 1) {
            temp[i].verificat = 1;
            temp[i].timpAsteptare = (timpCurent + 1) - temp[i].timpOcupare - temp[i].timpInceput;
            temp[i].timpProcesare = (timpCurent + 1) - temp[i].timpInceput;
            sumaTimpAsteptare += temp[i].timpAsteptare;
            sumaTimpProcesare += temp[i].timpProcesare;
        }
        j = i;
        min_timpOcupare = 9999;
        for (x = 0; x < n; x++) {
            if (temp[x].timpInceput <= (timpCurent + 1) && temp[x].verificat != 1) {
                if (min_timpOcupare != b[x] && min_timpOcupare > b[x]) {
                    min_timpOcupare = b[x];
                    i = x;
                }
            }
        }
    }

    timpMediuAsteptare = (float) sumaTimpAsteptare / n;
    timpMediuProcesare = (float) sumaTimpProcesare / n;

    auto end = chrono::high_resolution_clock::now();

    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;

    cout << "\nWall clock: " << fixed << time_taken << setprecision(9);
    cout << " sec";

    if (verbose) {
        printf(" %d", timpCurent);
        printf("\n Timpul mediu de asteptare = %0.2f\n Timpul mediu de procesare = %0.2f.\n \n", timpMediuAsteptare,
               timpMediuProcesare);
    }

}

void PRT_P(vector<proces> P, int n) {
    int i, t_total = 0, timpCurent, b[n], j, x, min_pr;
    int sumaTimpAsteptare = 0, sumaTimpProcesare = 0;
    float timpMediuAsteptare = 0.0, timpMediuProcesare = 0.0;
    proces temp[n];

    auto start = chrono::high_resolution_clock::now();

    for (i = 0; i < n; i++) {
        temp[i] = P[i];
        t_total += P[i].timpOcupare;
    }

    sort(temp, temp + (n - 1), compare);

    for (i = 0; i < n; i++)
        b[i] = temp[i].timpOcupare;

    i = j = 0;
    if (verbose) {
        printf("\n GANTT CHART\n\n %d %s", i, temp[i].nume.c_str());
    }
    for (timpCurent = 0; timpCurent < t_total; timpCurent++) {
        if (b[i] > 0 && temp[i].timpInceput <= timpCurent)
            b[i]--;

        if(verbose) {
            if (i != j)
                printf(" %d %s", timpCurent, temp[i].nume.c_str());
        }

        if (b[i] <= 0 && temp[i].verificat != 1) {
            temp[i].verificat = 1;
            temp[i].timpAsteptare = (timpCurent + 1) - temp[i].timpOcupare - temp[i].timpInceput;
            temp[i].timpProcesare = (timpCurent + 1) - temp[i].timpInceput;
            sumaTimpAsteptare += temp[i].timpAsteptare;
            sumaTimpProcesare += temp[i].timpProcesare;
        }
        j = i;
        min_pr = 9999;
        for (x = 0; x < n; x++) {
            if (temp[x].timpInceput <= (timpCurent + 1) && temp[x].verificat != 1) {
                if (min_pr != temp[x].prioritate && min_pr > temp[x].prioritate) {
                    min_pr = temp[x].prioritate;
                    i = x;
                }
            }
        }
    }

    timpMediuAsteptare = (float) sumaTimpAsteptare / n;
    timpMediuProcesare = (float) sumaTimpProcesare / n;

    auto end = chrono::high_resolution_clock::now();

    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;

    cout << "\nWall clock: " << fixed << time_taken << setprecision(9);
    cout << " sec";

    if (verbose) {
        printf(" %d", timpCurent);
    }
    printf("\n Timpul mediu de asteptare = %0.2f\n Timpul mediu de procesare = %0.2f.\n \n", timpMediuAsteptare,
           timpMediuProcesare);

}

int main() {
    int ch, n, Q = 0;
    string path50 = "../../data/data_50.txt";
    string path500 = "../../data/data_500.txt";
    string path1000 = "../../data/data_1000.txt";
    pair<vector<proces>, int> values;
    vector<proces> P;
    do {
        printf("\n Optiuni:");
        printf("\n 1. FCFS");
        printf("\n 2. SJF (Pre-emptive)");
        printf("\n 3. SJF (Non Pre-emptive)");
        printf("\n 4. Priority Scheduling (Pre-emptive)");
        printf("\n 5. Priority Scheduling (Non Pre-emptive)");
        printf("\n 6. Round Robin");
        printf("\n 7. Exit\n Optiunea ta : ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                values = fileRead(path50);
                n = values.second;
                P = values.first;
                FCFS(P, n);
                //////
                values = fileRead(path500);
                n = values.second;
                P = values.first;
                FCFS(P, n);
                //////
                values = fileRead(path1000);
                n = values.second;
                P = values.first;
                FCFS(P, n);
                //////
                break;
            case 2:
                values = fileRead(path50);
                n = values.second;
                P = values.first;
                SJF_P(P, n);
                //////
                values = fileRead(path500);
                n = values.second;
                P = values.first;
                SJF_P(P, n);
                //////
                values = fileRead(path1000);
                n = values.second;
                P = values.first;
                SJF_P(P, n);
                break;
            case 3:
                values = fileRead(path50);
                n = values.second;
                P = values.first;
                SJF_NP(P, n);
                //////
                values = fileRead(path500);
                n = values.second;
                P = values.first;
                SJF_NP(P, n);
                //////
                values = fileRead(path1000);
                n = values.second;
                P = values.first;
                SJF_NP(P, n);
                break;
            case 4:
                values = fileRead(path50);
                n = values.second;
                P = values.first;
                PRT_P(P, n);
                //////
                values = fileRead(path500);
                n = values.second;
                P = values.first;
                PRT_P(P, n);
                //////
                values = fileRead(path1000);
                n = values.second;
                P = values.first;
                PRT_P(P, n);
                break;
            case 5:
                values = fileRead(path50);
                n = values.second;
                P = values.first;
                PRT_NP(P, n);
                //////
                values = fileRead(path500);
                n = values.second;
                P = values.first;
                PRT_NP(P, n);
                //////
                values = fileRead(path1000);
                n = values.second;
                P = values.first;
                PRT_NP(P, n);
                break;
            case 6:
                /// quantumul reprezinta timpul maxim de executare pe care il are procesul la dispozitie
                printf("\n Introdu quantum : ");
                scanf("%d", &Q);

                values = fileRead(path50);
                n = values.second;
                P = values.first;
                RR(P, n, Q);
                //////
                values = fileRead(path500);
                n = values.second;
                P = values.first;
                RR(P, n, Q);
                //////
                values = fileRead(path500);
                n = values.second;
                P = values.first;
                RR(P, n, Q);
                break;
            default:
                exit(0);
        }
    } while (ch != 7);
    return 0;
}