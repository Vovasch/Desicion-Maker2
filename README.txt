Decision-Maker 2

This project is in process of developing under my programing teacher coordination. This is a part of a big device for military/police needs. This device defines kind of the sounds and the direction where the sound came. Our specialization is only first part.
We have a recording of sounds transferred into cepstral coefficients and using GMM (Gaussian mixture model) we need to define where and which sound was on this recording comparing them with pretrained bases.


///////////////////  Libraries and dependencies for project:

1) mlpack

Here is link with manual about how to get mlpack running and up: https://www.mlpack.org/getstarted.html

We need mlpack to have all math that calculate probabilites, to train bases and to load them into program.

2)dirent.h

This library just needs to be downloaded and passed into include file with all other libraries.

We need dirent.h to list through folders and calculate amount of bases.


///////////////////  General info

This program can be started through a consol. All you need is to enter name of file you want to test or name this file with a default name: "main.txt" and just start the program.

Bases should be pretrained with mlpack instuments: mlpack_gmm_train.exe and then transferred to directory data\models. Transferred 

You also have to leave a describing for each base where would be such parameters:

MAX_VALUE_TO_BE_DEFINED: 22.2
MIN_VALUE_TO_BE_DEFINED: 2
THE_LEAST_DURATION: 50
THE_LONGEST_DURATION: -1

And transfer them into directory: data/models_description.

The some magic is onto happening, but we still think about kind of this magic.

We(me and my teacher) thought about Viterby algorithm, but tests showed that this algorithm doesn't match our needs.

Results will be like: Sound "bird" started on 2d second and stopped on 5th seconds.
