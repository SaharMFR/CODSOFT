import pandas as pd
from math import sqrt
import numpy as np
import matplotlib.pyplot as plt
# %matplotlib inline
import re

movies_df = pd.read_csv('movies.csv')

ratings_df = pd.read_csv('ratings.csv')


movies_df['year'] = movies_df['title'].str.extract('(\(\d\d\d\d\))', expand=False)
movies_df['year'] = movies_df['year'].str.extract('(\d\d\d\d)', expand=False)
# movies_df['title'] = movies_df['title'].str.replace('(', '')
# movies_df['title'] = movies_df['title'].str.replace('0', '')
# movies_df['title'] = movies_df['title'].str.replace('1', '')
# movies_df['title'] = movies_df['title'].str.replace('2', '')
# movies_df['title'] = movies_df['title'].str.replace('3', '')
# movies_df['title'] = movies_df['title'].str.replace('4', '')
# movies_df['title'] = movies_df['title'].str.replace('5', '')
# movies_df['title'] = movies_df['title'].str.replace('6', '')
# movies_df['title'] = movies_df['title'].str.replace('7', '')
# movies_df['title'] = movies_df['title'].str.replace('8', '')
# movies_df['title'] = movies_df['title'].str.replace('9', '')
# movies_df['title'] = movies_df['title'].str.replace(')', '')

# movies_df['year'] = movies_df['title'].str.extract('(\(\d\d\d\d\))', expand=False)
# movies_df['year'] = movies_df['year'].str.extract('(\d\d\d\d)', expand=False)

movies_df['title'] = movies_df['title'].str.replace('(\(\d\d\d\d\))', '', regex=True)

movies_df['title'] = movies_df['title'].apply(lambda x: x.strip())
print(movies_df['title'])

print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")

print(movies_df['year'])

print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")

# movies_df = movies_df.drop('genres')
# print(movies_df)

userInput = [
    {'title': 'Breakfast Club, The', 'rating': 5},
    {'title': 'Toy Story', 'rating': 3.5},
    {'title': 'Jumanji', 'rating': 2},
    {'title': 'Pulp Fiction', 'rating': 5},
    {'title': 'Akira', 'rating': 4.5}
]


inputMovies = pd.DataFrame(userInput)
print(inputMovies)

print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")


# print(movies_df['title'])
# print(inputMovies['title'])
inputId = movies_df[movies_df['title'].isin(inputMovies['title'].tolist())]
print(inputId)

print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")

inputMovies = pd.merge(inputId, inputMovies)

print(inputMovies)

print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")

# inputMovies = inputMovies.drop('year')

# print(inputMovies)

userSubset = ratings_df[ratings_df['movieId'].isin(inputMovies['movieId'].tolist())]

print(userSubset.head(6))

print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")


userSubsetGroup = userSubset.groupby(['userId'])

print(userSubsetGroup.get_group(3))

print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")

userSubsetGroup = sorted(userSubsetGroup, key=lambda x: len(x[1]), reverse=True)

print(userSubsetGroup[3])


print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")

userSubsetGroup = userSubsetGroup[0:100]
# print("\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/")
# print("\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/")
# print("\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/")

# print(userSubsetGroup)

print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")

pearsonCorrelationDict = {}
for name, group in userSubsetGroup:
    group = group.sort_values(by='movieId')
    inputMovies = inputMovies.sort_values(by='movieId')
    nRatings = len(group)
    temp_df = inputMovies[inputMovies['movieId'].isin(group['movieId'].tolist())]
    tempRatingList = temp_df['rating'].tolist()
    tempGroupList = group['rating'].tolist()

    Sxx = sum([i**2 for i in tempRatingList]) - pow(sum(tempRatingList), 2)/float(nRatings)
    Syy = sum([i**2 for i in tempGroupList]) - pow(sum(tempGroupList), 2)/float(nRatings)
    Sxy = sum(i*j for i, j in zip(tempRatingList, tempGroupList)) - sum(tempRatingList)*sum(tempGroupList)/float(nRatings)

    if Sxx != 0 and Syy != 0:
        pearsonCorrelationDict[name] = Sxy/sqrt(Sxx*Syy)
    else:
        pearsonCorrelationDict[name] = 0

pearsonDF = pd.DataFrame.from_dict(pearsonCorrelationDict, orient='index')
print(pearsonDF.head())
print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")

pearsonDF.columns = ['similarityIndex']
print(pearsonDF.head())
print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")

pearsonDF['userId'] = pearsonDF.index.map(lambda x: str(x)[1:-2])
print(pearsonDF['userId'])
print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")

# pearsonDF['userId'] = pearsonDF['userId'].str[10:-2]
# pearsonDF['userId'] = pearsonDF['userId'].replace(',)', '')

# print(pearsonDF['userId'])

# print("----------------------------------------------------------------------")
# print("----------------------------------------------------------------------")
# print("----------------------------------------------------------------------")


pearsonDF.index = range(len(pearsonDF))

print(pearsonDF.head(10))

print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")

topUsers = pearsonDF.sort_values(by='similarityIndex', ascending=False)[0:50]

print(topUsers.head())

print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")


topUsersRating = topUsers.merge(ratings_df, left_on='userId', right_on='userId', how='inner')

print(topUsersRating.head())
print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")

topUsersRating['weightedRating'] = topUsersRating['similarityIndex']*topUsersRating['rating']
print(topUsersRating.head())
print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")

tempTopUsersRating = topUsersRating.groupby('movieId').sum()[['similarityIndex','weightedRating']]
tempTopUsersRating.columns = ['sum_similarityIndex','sum_weightedRating']
tempTopUsersRating.head()
print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")

recommendation_df = pd.DataFrame()
recommendation_df['weighted average recommendation score'] = tempTopUsersRating['sum_weightedRating']/tempTopUsersRating['sum_similarityIndex']
recommendation_df['movieId'] = tempTopUsersRating.index
recommendation_df.head()
print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")


recommendation_df = recommendation_df.sort_values(by='weighted average recommendation score', ascending=False)
recommendation_df.head(10)
print("----------------------------------------------------------------------")
print("----------------------------------------------------------------------")
