class MatrixIndexError(Exception):
    pass


class MatrixActionError(Exception):
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
    '''Класс для работы с матрицами'''
    acc = 5

    def __init__(self, size=10, data=None):  # среди числа столбцов и числа строк
        self.size = size
        self.data = data

    def transpose(self):
        data = self.data
        data = [list(col) for col in zip(*data)]
        return Matrix(max(len(data), len(data[0])), data)

    def add_string_to_matrix(self, string=None):
        size = self.size
        data = self.data

        if len(data) == size or len(string) > size:
            raise MatrixActionError('невозможная операция. размер максимальной квадратной матрици фиксирован и равен -> ', size)
        try:
            if len(data[-1]) != len(string):
                raise MatrixActionError('невозможно добавить строку к матрице из-за несовпадения размеров')
        except IndexError:
            return Matrix(size, data.append(string))
        return Matrix(size, data.append(string))

    def add_column_to_matrix(self, column=None):
        size = self.size
        data = self.data
        if len(data) != len(column) or size < len(column):
            raise MatrixActionError('невозможно добавить столбец к матрице из-за несовпадения размеров')
        elif len(data) == 0:
            for i in column:
                data.append(i)
            return Matrix(size, data)
        for i in range(len(column)):
            data[i].append(column[i])
        return Matrix(size, data)

    def count_determinant_gauss_method(self):  # алгоритм Гаусса для рассчета определителя матрицы
        data_n = self.data[:]
        size = self.size
        inverse_counter = 0
        summ = 1
        if len(data_n) != len(data_n[1]):  # проверка на то, квадратная ли матрица
            raise MatrixIndexError('матрица не квадратная')
        for _ in range(size):
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
            if data_n[0][0] == 0:
                return 0
            for i in range(len(data_n[0]) - 1, -1, -1):  # деление 1 строчки на 1 элемент
                data_n[0][i] /= data_n[0][0]
            for i in data_n[1:]:  # вычитание первой строчки из всех остальных с целью занульть 1 столбец
                for j in range(len(i) - 1, -1, -1):
                    # if i[j] > 0:
                    #     i[j] -= abs(data_n[0][j] * i[0])
                    # else:
                    #     i[j] += abs(data_n[0][j] * i[0])
                    i[j] -= data_n[0][j] * i[0]

            for i in range(len(data_n)):  # вычеркивание 1 столбца
                data_n[i] = data_n[i][1:]
            data_n = data_n[1:]  # вычеркивание 1 строчки и получение разложение матрицы по столбцу
            if len(data_n) == 1:  # получение итогового ответа после разложение матрицы 2 порядка
                k = summ * ((-1) ** inverse_counter) * data_n[0][0]  # через столбец к матрице 1 порядка
                if k // 10 == 0:
                    return k
                return round(k, Matrix.acc)

    def count_rank_gauss_method(self):
        data_n = self.data
        len_st = len(data_n)
        len_col = len(data_n[0])
        rank = 0
        for _ in range(len_st):
            rank += 1  # сохранение ранга
            a11 = data_n[0][0]
            if a11 == 0:
                return rank
            for j in range(len_col - rank + 1):
                data_n[0][j] /= a11
            for j in data_n[1:]:  # вычитание первой строчки из всех остальных с целью занульть 1 столбец
                for z in range(len(j) - 1, -1, -1):
                    j[z] -= data_n[0][z] * j[0]
            for j in range(len(data_n)):  # вычеркивание 1 столбца
                data_n[j] = data_n[j][1:]
            data_n = data_n[1:]  # вычеркивание 1 строчки и получение разложение матрицы по столбцу
            if len(data_n) == 1 and data_n[0][0] != 0:
                return rank + 1
            else:
                return rank

    def custom_print(self):
        data = self.data[:]
        for i in data:
            for j in i:
                print(j, end=' ')
            print()
        print()

    def minor(self, st, col):  # вычеркивает st и col из матрицы
        data = self.data
        answer = data[:st] + data[st + 1:]
        for i in range(len(answer)):
            answer[i] = answer[i][:col] + answer[i][col + 1:]
        return Matrix(len(answer), answer)

    def determinant_for_2_matrix(self):
        data = self.data
        if len(data) != 2:
            raise ValueError('матрица должна иметь порядок 2')
        return data[0][0] * data[1][1] - data[0][1] * data[1][0]

    def determinant_for_3_matrix(self):
        data = self.data
        if len(data) != 3:
            raise ValueError('матрица должна иметь порядок 3')
        k = data[0][0] * data[1][1] * data[2][2] + \
               data[0][1] * data[1][2] * data[2][0] + \
               data[0][2] * data[1][0] * data[2][1] - \
               data[0][2] * data[1][1] * data[2][0] - \
               data[0][1] * data[1][0] * data[2][2] - \
               data[0][0] * data[1][2] * data[2][1]
        if k // 10 == 0:
            return k
        return round(k, Matrix.acc)

    def find_allied_matrix(self):
        data = self.data
        answer = []
        l = len(data)
        if l != len(data[0]):
            raise ValueError('этот метод определен только для квадратных матриц')
        for i in range(l):
            answer.append([0] * l)
        for i in range(l):
            for j in range(l):
                alg_dop = Matrix(len(data), data).minor(i, j)
                if alg_dop.what_now_size() == 2:
                    alg_dop = alg_dop.determinant_for_2_matrix()
                elif alg_dop.what_now_size() == 3:
                    alg_dop = alg_dop.determinant_for_3_matrix()
                else:
                    alg_dop = alg_dop.count_determinant_gauss_method()
                answer[i][j] = alg_dop * ((-1) ** (i + j))
        return Matrix(len(answer), answer)

    def find_inverse_matrix(self):
        return Matrix(len(self.data), self.data).transpose().find_allied_matrix().number_mul(1/Matrix(len(self.data), self.data).count_determinant_gauss_method())
        # data = self.data
        # k = Matrix(len(data), data).find_allied_matrix()

    def what_max_size(self):
        return self.size

    def what_now_size(self):
        data = self.data
        if len(data) == len(data[0]):
            return len(data)
        return len(data), len(data[0])

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
        return Matrix(size, data1)

    def __iadd__(self, other):
        data1 = self.data
        size = self.size
        data2 = other.data
        return Matrix(size, data1) + Matrix(size, data2)

    def number_mul(self, number):
        data = self.data
        size = self.size
        for i in range(len(data)):
            for j in range(len(data[i])):
                data[i][j] *= number
                if data[i][j] == 0:
                    data[i][j] = int(abs(data[i][j]))
        return Matrix(size, data)

    def __sub__(self, other):
        data1 = self.data
        size = self.size
        data2 = other.data
        if len(data1) != len(data2) or len(data2[0]) != len(data1[0]):
            raise MatrixIndexError('неверные индексы матриц')
        for i in range(len(data1)):
            for j in range(len(data1[i])):
                data1[i][j] -= data2[i][j]
        return Matrix(size, data1)

    def __isub__(self, other):
        data1 = self.data[:]
        size = self.size
        data2 = other.data
        return Matrix(size, data1) - Matrix(size, data2)

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
                    answer[i][j] += (data1[i][k] * data2[j][k])
        return Matrix(max(len(data1), len(data2)), answer)

    def __imul__(self, other):
        data1 = self.data
        data2 = other.data
        return Matrix(max(len(data1), len(data1[0])), data1) * Matrix(max(len(data2), len(data2[0])), data2)

    def __str__(self):
        # '\n'.join(' '.join([[str(self.data[i][j]) for j in range(len(self.data[i]))] for i in range(len(self.data))][j][i] for i in range(len([[str(self.data[i][j]) for j in range(len(self.data[i]))] for i in range(len(self.data))][j]))) for j in range(len([[str(self.data[i][j]) for j in range(len(self.data[i]))] for i in range(len(self.data))])))
        data_n = self.data
        answer = ''
        data_n = [[str(data_n[i][j]) for j in range(len(data_n[i]))] for i in range(len(data_n))]
        answer = '\n'.join(' '.join(data_n[j][i] for i in range(len(data_n[j]))) for j in range(len(data_n)))
        # for i in range(len(data_n)):
        #     print('<', data_n[i], '>')
        #     a = ' '.join(data_n[i])
        #     answer += a + '\n'
        return answer

    def __truediv__(self, other):
        return Matrix(len(self.data), self.data) * Matrix(len(other.data), other.data).find_inverse_matrix()

    def __itruediv__(self, other):
        return Matrix(len(self.data), self.data) / Matrix(len(other.data), other.data)

    def __int__(self):
        raise MatrixActionError('невозможно преобразовать тип Matrix к типу Integer')

    def __float__(self):
        raise MatrixActionError('невозможно преобразовать тип Matrix к типу Float')

    # def __del__(self):
    #     class_name = self.__class__.__name__
    #     print('объект {} удален'.format(class_name))


# b = Matrix(3, [[1, 1, 1], [3, 1, 1], [1, 3, 1]])
# c = Matrix(4, [[1, 2, 3, 4], [5, 6, 7, 8], [9, 16, 11, 12], [13, 14, 15, 10]])
