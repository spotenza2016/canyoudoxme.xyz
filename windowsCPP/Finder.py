#Libraries
import sys
import tweepy

#API Codes
auth = tweepy.OAuth1UserHandler('coO1IyfiITlmgr2RrxzHwiAtW', 'Dfe7AnynDEiwWL13I2F839CsL2WpBMC2yWG1buDQGGRMO8vQCt', '796095365284069376-bs5fawV7w6hbqZOyg4jf8lQGipLhJNY', '6Gp6HlIznoazj4j89iX6wts4LMwLxDwlTQwLJhlVM3e0L')

#Get the API
api = tweepy.API(auth)

#Clear the text file
with open('data.txt', 'w') as f:
    print()
    
#If one argument was given
if  len(sys.argv) == 2:   
    #Number of tweets gotten
    numTweets = 0
    
    #Generate first set
    tweets = api.user_timeline(screen_name = sys.argv[1], count = 20, exclude_replies = True, include_rts = False)
    maxID = tweets[len(tweets) - 1].id - 1
    
    #While under the tweet requirement and while tweets remain
    while numTweets < 15:       
        #Get new tweets
        if numTweets != 0:
            tweets = api.user_timeline(screen_name = sys.argv[1], count = 20, max_id = maxID, exclude_replies = True, include_rts = False)
        
        #Are tweets remaining
        if len(tweets) == 0:
            break
        
        #Get the new number of tweets
        numTweets = numTweets + len(tweets)
        
        #Set the new max ID
        maxID = tweets[len(tweets) - 1].id - 1
        
        #Append every tweet
        for tweet in tweets:
            with open('data.txt', 'a') as f:
                print(tweet.text, file = f)
                
#If given two arguments
elif len(sys.argv) == 3:
    #Get the user
    user = api.get_user(screen_name = sys.argv[1])
    
    #Print their bio location
    with open('data.txt', 'a') as f:
        print(user.location, file = f)
        
#If given one argument
elif len(sys.argv) == 1:
    #Get a random user
    user = api.home_timeline(count = 1)[0].user
    
    #Print their screen name
    with open('data.txt', 'a') as f:
        print(user.screen_name, file = f)