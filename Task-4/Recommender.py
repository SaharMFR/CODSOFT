import pandas as pd
from math import sqrt

moviesDF = pd.read_csv('movies.csv')

ratingsDF = pd.read_csv('ratings.csv')


moviesDF['year'] = moviesDF['title'].str.extract('(\(\d\d\d\d\))', expand=False)
moviesDF['year'] = moviesDF['year'].str.extract('(\d\d\d\d)', expand=False)
moviesDF['title'] = moviesDF['title'].str.replace('(\(\d\d\d\d\))', '', regex=True)
moviesDF['title'] = moviesDF['title'].apply(lambda x: x.strip())

# User's rated movies.
# Movies that start with 'The' have been written : 'movieNameWithoutThe, The'.

userInput = [
    {'title': 'Home alone', 'rating': 4},
    {'title': 'Harry potter', 'rating': 5},
    {'title': 'Toy Story', 'rating': 5},
    {'title': 'Jumanji', 'rating': 4.5},
    {'title': 'Superman', 'rating': 3.5},
    {'title': 'Final destination', 'rating': 2.5},
    {'title': 'Breakfast Club, The', 'rating': 4},
]


inputMovies = pd.DataFrame(userInput)

inputId = moviesDF[moviesDF['title'].isin(inputMovies['title'].tolist())]

inputMovies = pd.merge(inputId, inputMovies)

usersWithSameMovies = ratingsDF[ratingsDF['movieId'].isin(inputMovies['movieId'].tolist())]

usersGrouped = usersWithSameMovies.groupby(['userId'])
usersGrouped = sorted(usersGrouped, key=lambda x: len(x[1]), reverse=True)
usersGrouped = usersGrouped[0:100]

pearsonCorrelationDict = {}
for ID, group in usersGrouped:
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
        pearsonCorrelationDict[ID] = Sxy/sqrt(Sxx*Syy)
    else:
        pearsonCorrelationDict[ID] = 0

pearsonDF = pd.DataFrame.from_dict(pearsonCorrelationDict, orient='index')
pearsonDF.columns = ['similarityIndex']

pearsonDF['userId'] = pearsonDF.index.map(lambda x: int(str(x)[1:-2]))
pearsonDF.index = range(len(pearsonDF))

topUsers = pearsonDF.sort_values(by='similarityIndex', ascending=False)[0:50]

topUsersRatings = topUsers.merge(ratingsDF, left_on='userId', right_on='userId', how='inner')
topUsersRatings['weightedRating'] = topUsersRatings['similarityIndex'] * topUsersRatings['rating']

tempTopUsersRatings = topUsersRatings.groupby('movieId').sum()[['similarityIndex', 'weightedRating']]
tempTopUsersRatings.columns = ['sum_similarityIndex', 'sum_weightedRating']

recommendationDF = pd.DataFrame()
recommendationDF['weighted average recommendation score'] = tempTopUsersRatings['sum_weightedRating'] / tempTopUsersRatings['sum_similarityIndex']
recommendationDF['movieId'] = tempTopUsersRatings.index
recommendationDF = recommendationDF.sort_values(by='weighted average recommendation score', ascending=False)
recommendationDF.index = range(len(recommendationDF))
recommendationDF = recommendationDF.merge(moviesDF, left_on='movieId', right_on='movieId', how='inner')

watched = recommendationDF[recommendationDF['movieId'].isin(inputMovies['movieId']).tolist()]

print("\nHere is some recommended movies :\n\n")

for i in range(10):
    if recommendationDF['title'].loc[i] not in watched['title'].tolist():
        print(i + 1, "-", recommendationDF['title'].loc[i], "   (", recommendationDF['year'].loc[i], ")")
