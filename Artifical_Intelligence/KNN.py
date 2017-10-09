# -*- coding: utf-8 -*-

from numpy import *
import operator
import time

SIZE_OF_DATA = 5
SIZE_OF_TEST = 5

def read_input(filename):
    with open(filename) as fr:
        corpus = []
        for text in fr.readlines()[1:]:
            for word in text.strip().split('\t')[1].split():
                corpus.append(word)
        allwords = set(corpus)

    matN = len(allwords)
    returnMat = zeros((SIZE_OF_DATA + SIZE_OF_TEST, matN))
    shares = []
    index = 0
    with open(filename) as fr:
        for line in fr.readlines()[1:]:
            setFromLine = set(line.strip().split('\t')[1].split())
            oneLine = []
            for s in allwords:
                if s in setFromLine:
                    oneLine.append(1)
                else:
                    oneLine.append(0)
            returnMat[index, :] = oneLine
            if index < SIZE_OF_DATA:
                shares.append(float(line.strip().split('\t')[-1].strip()))
            index += 1
    return returnMat[:SIZE_OF_DATA,:], returnMat[SIZE_OF_DATA:,:], shares

def norm(inputMat):             #归一化输入矩阵
    outputMat = inputMat.copy()
    m, n = shape(inputMat)      #行，列大小
    for i in range(m):
        lineSum = sum(inputMat[i, :])    #这行的和
        for j in range(n):
            outputMat[i, j] = inputMat[i, j] / lineSum   #归一化频率
    return outputMat           #返回归一化后的矩阵

def cosSim(a, b):
    inA = mat(a)
    inB = mat(b)
    num = float(inA * inB.T)
    denom = linalg.norm(inA) * linalg.norm(inB)
    return num / denom

def pearsSim(a, b):
    inA = mat(a)
    inB = mat(b)
    if len(inA) < 25:
        return 1.0
    return 0.5 + 0.5 * corrcoef(intA, inB, rowvar=0)[0][1]

def eulidSim(a, b):
    return 1.0 / (1.0 + linalg.norm(a - b))

def classify(k, trainDataSet, testDataSet, dataShares):
    predictShares = []
    for testVector in testDataSet:
        dis = []
        for trainVector in trainDataSet:
            dis.append(linalg.norm(testVector - trainVector)) # 欧式距离
            #dis.append(sum(list(map(abs, testVector - trainVector)))) # 曼哈顿距离
            #dis.append(cosSim(testVector, trainVector)) # 夹角余弦
            #dis.append(pearsSim(testVector, trainVector)) # 皮尔逊相关系数
            #dis.append(eulidSim(testVector, trainVector)) # 归一化欧式距离
        nearest_item = list(range(SIZE_OF_DATA))
        nearest_item.sort(key=lambda x : dis[x])
        indexSum = 0.0
        for index in nearest_item[:k]:
            indexSum += dataShares[index]
        predictShares.append(indexSum / k)
    return predictShares

def main():
    trainMat, testMat, shares = read_input('Dataset.txt') #训练文档，测试矩阵，
    normTrainMat = norm(trainMat)       #得到归一化的训练矩阵
    normTestMat = norm(testMat)         #得到归一化的测试矩阵
	
	
	
    predictShares = classify(1, normTrainMat, normTestMat, shares)        #分类吧？
    print(predictShares)

if __name__ == '__main__':
    main()