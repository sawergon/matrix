class MatrixIndexError(Exception):
    pass


def string_changer(data, pos, to):
    if 0 > to + pos > len(data):
        return data
    data[pos], data[pos + to] = data[pos + to], data[pos]
    return data


def list_rot90(data, times=1):
    return [list(reversed(col)) for col in zip(*data)]


def column_changer(data, pos, to):
    if 0 > to + pos > len(data[0]):
        return data
    for i in data:
        i[pos], i[pos + to] = i[pos + to], i[pos]
    return data


class Matrix:  # если требуется создать неквадратную матрицу то в size следует ввести наибольшее
    def __init__(self, size=10, data=None):  # среди числа столбцов и числа строк
        self.size = size
        self.data = data

    def transpose(self):
        data = self.data
        data = [list(reversed(col)) for col in zip(*data)]
        data = Matrix(max(len(data), len(data[0])), data)
        return data

    def add_string_to_matrix(self, string=None):
        size = self.size
        data = self.data

        if len(data) == size or len(string) > size:
            print('невозможная операция. размер квадратной матрици фиксирован и равен -> ', size)
            return data
        try:
            if len(data[-1]) != len(string):
                print('невозможно добавить строку к матрице из-за несовпадения размеров')
                return data
        except IndexError:
            return data.append(string)
        return data.append(string)

    def add_column_to_matrix(self, column=None):
        size = self.size
        data = self.data
        if len(data) != len(column) or size < len(column):
            print('невозможно добавить столбец к матрице из-за несовпадения размеров')
            return data
        elif len(data) == 0:
            for i in column:
                data.append(i)
            return data
        for i in range(len(column)):
            data[i].append(column[i])
        return data

    def count_determinant_gauss_method(self):  # алгоритм Гаусса для рассчета определителя матрицы
        data_n = self.data[:]
        size = self.size
        inverse_counter = 0
        summ = 1
        if len(data_n) != len(data_n[1]):  # проверка на то, квадратная ли матрица
            print('матрица не квадратная')
            return data_n
        for z in range(size):
            h = []
            for i in range(len(data_n)):  # вычисление максимального элемента в матрице
                if abs(max(data_n[i])) > abs(min(data_n[i])):
                    s = max(data_n[i])
                else:
                    s = min(data_n[i])
                try:
                    if abs(s) > abs(h[0]):
                        h = [s, i, data_n[i].index(s)]
                except IndexError:
                    h = [s, i, data_n[i].index(s)]
            inverse_counter += (h[1] + h[2])  # подсчет инверсий необходимых для перестановки максимального элемента
            # print(h, z, data_n)               # матрицы на место [0][0]
            for i in range(h[1], 0, -1):  # смежные перестановки и приведение строки с максимальным элементом на 1 место
                data_n = string_changer(data_n, i, -1)
            for i in range(h[2], 0, -1):  # смежные перестановки и приведение столба с максимальным элементом на 1 место
                data_n = column_changer(data_n, i, -1)
            summ *= data_n[0][0]  # сохранение элемента с иднексом 00 для дальнейшего разложения матрицы через столбец
            for i in range(len(data_n[0]) - 1, -1, -1):  # деление 1 строчки на 1 элемент
                data_n[0][i] /= data_n[0][0]
            for i in data_n[1:]:  # вычитание первой строчки из всех остальных с целью занульть 1 столбец
                for j in range(len(i) - 1, -1, -1):
                    if i[j] > 0:
                        i[j] -= abs(data_n[0][j]*i[0])
                    else:
                        i[j] += abs(data_n[0][j] * i[0])
            for i in range(len(data_n)):  # вычеркивание 1 столбца
                data_n[i] = data_n[i][1:]
            data_n = data_n[1:]  # вычеркивание 1 строчки и получение разложение матрицы по столбцу
            if len(data_n) == 1:  # получение итогового ответа после разложение матрицы 2 порядка
                return summ*((-1) ** inverse_counter)*data_n[0][0]  # через столбец к матрице 1 порядка

    def custom_print(self):
        data = self.data[:]
        for i in data:
            for j in i:
                print(j, end=' ')
            print()
        print()
    def minor(self, st, col):
        data = self.data
        answer = data[:st] + data[st + 1:]
        for i in range(len(answer)):


    def determinant_for_2_matrix(self):
        data = self.data
        if len(data) != 2:
            raise ValueError('матрица должна иметь порядок 2')
        return data[0][0] * data[1][1] - data[0][1] * data[1][0]

    def determinant_for_3_matrix(self):
        data = self.data
        if len(data) != 3:
            raise ValueError('матрица должна иметь порядок 3')
        return data[0][0] * data[1][1] * data[2][2] +\
               data[0][1] * data[1][2] * data[2][0] +\
               data[0][2] * data[1][0] * data[2][1] -\
               data[0][2] * data[1][1] * data[2][0] -\
               data[0][1] * data[1][0] * data[2][2] -\
               data[0][0] * data[1][2] * data[2][1]

    def find_allied_matrix(self):
        data = self.data
        answer = []
        l = len(data)
        alg_dop = []
        if l != len(data[0]):
            raise ValueError('этот метод определен только для квадратных матриц')
        for i in range(l):
            answer.append([0] * l)
        for i in range(l):
            for j in range(l):
                alg_dop = data[:i] + data[i + 1:]
                for i in range(len(alg_dop)):
                    alg_dop[i]

    def find_inferse_matrix(self):
        data = self.data
        o =

    def what_max_size(self):
        return self.size

    def how_many_strings(self):
        return len(self.data)

    def how_many_columns(self):
        return len(self.data[0])

    def __eq__(self, other):
        data1 = self.data
        data2 = other.data
        if len(data1) != len(data2):
            return False
        for i in range(len(data1)):
            if len(data1[i]) != len(data2[i]):
                return False
        for i in range(len(data2)):
            for j in range(len(data2[i])):
                if data2[i][j] != data1[i][j]:
                    return False
        return True

    def __add__(self, other):
        data1 = self.data
        size = self.size
        data2 = other.data
        if len(data1) != len(data2) or len(data2[0]) != len(data1[0]):
            raise MatrixIndexError('неверные индексы матриц')
        for i in range(len(data1)):
            for j in range(len(data1[i])):
                data1[i][j] += data2[i][j]
        data1 = Matrix(size, data1)
        return data1

    def __iadd__(self, other):
        data1 = self.data
        size = self.size
        data2 = other.data
        data1 = Matrix(size, data1)
        data2 = Matrix(size, data2)
        return data1 + data2

    def number_mul(self, number):
        data = self.data
        size = self.size
        for i in range(len(data)):
            for j in range(len(data[i])):
                data[i][j] *= number
        data = Matrix(size, data)
        return data

    def __sub__(self, other):
        data1 = self.data
        size = self.size
        data2 = other.data
        if len(data1) != len(data2) or len(data2[0]) != len(data1[0]):
            raise MatrixIndexError('неверные индексы матриц')
        for i in range(len(data1)):
            for j in range(len(data1[i])):
                data1[i][j] -= data2[i][j]
        data1 = Matrix(size, data1)
        return data1

    def __isub__(self, other):
        data1 = self.data[:]
        size = self.size
        data2 = other.data
        data1 = Matrix(size, data1)
        data2 = Matrix(size, data2)
        return data1 - data2

    def __mul__(self, other):
        data1 = self.data
        data2 = other.data
        answer = []
        for i in range(len(data2[0])):
            answer.append([0] * len(data1))
        if len(data2) != len(data1[0]):
            raise MatrixIndexError('неверное колличество строк и столбцов')
        data2 = list_rot90(data2)
        for i in range(len(data2)):
            data2[i] = data2[i][::-1]
        for i in range(len(data1)):
            for j in range(len(data2)):
                for k in range(len(data2[j])):
                    answer[i][j] += (data1[i][k]*data2[j][k])
        answer = Matrix(max(len(data1), len(data2)), answer)
        return answer

    def __imul__(self, other):
        data1 = self.data
        data2 = other.data
        data1 = Matrix(max(len(data1), len(data1[0])), data1)
        data2 = Matrix(max(len(data2), len(data2[0])), data2)
        return data1 * data2

    def __str__(self):
        return str(self.data)

    def __truediv__(self, other):
        data1 = self.data
        data2 = other.data



a = Matrix(3, [[1, 2, 1], [1, 2, 1]])
b = Matrix(3, [[1, 1], [3, 1], [1, 3]])
a.custom_print()
b.custom_print()
a *= b
a.custom_print()
b.custom_print()
b = b.transpose()
b.custom_print()
b = Matrix.number_mul(b, 3)
b.custom_print()

