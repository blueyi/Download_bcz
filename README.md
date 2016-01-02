## About   
`Download.exe` is a batch download program based on wget, `get_nodup_word_tv_url.exe` used to obtain unduplicated direct http url,`get_try_tv_url_ex_word.exe` can used to predict bcz's tv url. `get_url_ex_url.exe` to get unduplicated url from more than one text file. `get_nodup_word_list.exe` to get unduplicated word from more than one text file.`Rename.exe` used to rename downloaded file to original file name.`Copy_words.exe` used to copy file from a source directory,the file name specified by a text file,the destination directory will be named `words_list`.

## Main feature  
This program will download all resource file from an text file on the basis of what pattern of url line the text file contain.This program only used to technical communication, so don't used in any illegal field.    

## Download  
You can download the latest available version in [release](https://github.com/blueyi/Download_bcz/tree/master/release) directory, or download the program you need from github release option.  
There are some test `text file` and downloaded complete file in root directory.  

## How to use it  
1.Get the file name and url you want to download, and store them in an text file, one per row.eg:  
>word_test.txt

```
hold on	/word_audios_dat/hold on.dat
hold on	/word_audios_dat/hold on.dat
learn (know) sth. by heart	/word_audios_dat/learn _know_ sth_ by heart.dat
```
your downloaded file stored will be `hold on_test.dat`  

2.Run command line `Download.exe test1.txt` start download, when the download has completed, you will find a directory named of `word_test`, which contain all of file you need.  

3.Run command line `get_nodup_word_tv_url.exe file1.txt file2.txt` to get unduplicated url to a file named `Nodup_tv.txt`,eg:  
>file1.txt

```
adjustable	/word_tv/real_adjustable.mp4
admiration	/word_tv/noun_admiration.mp4
adolescent	/word_tv/real_adolescent.mp4
```
>file2.txt

```
admiration	/word_tv/noun_admiration.mp4
adore	/word_tv/music_adore.mp4
aerial	/word_tv/news_play_video_871.mp4
```
you will get   
>Nodup_tv.txt

```
adjustable	/word_tv/real_adjustable.mp4
admiration	/word_tv/noun_admiration.mp4
adolescent	/word_tv/real_adolescent.mp4
adore	/word_tv/music_adore.mp4
aerial	/word_tv/news_play_video_871.mp4
```
Then maybe you would like to run command line `Download.exe -d Total_tv.txt to download directly`

4.Run command line `get_try_tv_url_ex_word.exe word_list.txt exclude.txt` to get a predicted text file named of `Try_tv.txt`, which contain a list of word in word_list.txt and its tv url, but exclude the words in exclude.txt, the exclude.txt is an optional arrgument.eg:  
>word_list.txt

```
abide	
abundance	
accommodate	/word_tv/news_play_video_1937.mp4
```
>exclude.txt

```
abundance   /word_tv/real_abundance.mp4
accord
```
Run command line `get_try_tv_url_ex_word.exe word_list.txt`,you will get  
>Try_tv.txt

```
abide	http://baicizhan.qiniucdn.com/word_tv/real_abide.mp4
abide	http://baicizhan.qiniucdn.com/word_tv/animate_abide.mp4
abide	http://baicizhan.qiniucdn.com/word_tv/leng_abide.mp4
abide	http://baicizhan.qiniucdn.com/word_tv/noun_abide.mp4
abide	http://baicizhan.qiniucdn.com/word_tv/abide.mp4
abundance	http://baicizhan.qiniucdn.com/word_tv/real_abundance.mp4
abundance	http://baicizhan.qiniucdn.com/word_tv/animate_abundance.mp4
abundance	http://baicizhan.qiniucdn.com/word_tv/leng_abundance.mp4
abundance	http://baicizhan.qiniucdn.com/word_tv/noun_abundance.mp4
abundance	http://baicizhan.qiniucdn.com/word_tv/abundance.mp4
accommodate	http://baicizhan.qiniucdn.com/word_tv/news_play_video_1937.mp4
```
Run command line `get_try_tv_url_ex_word.exe word_list.txt ex.txt`,you will get  
>Try_tv.txt

```
abide	http://baicizhan.qiniucdn.com/word_tv/real_abide.mp4
abide	http://baicizhan.qiniucdn.com/word_tv/animate_abide.mp4
abide	http://baicizhan.qiniucdn.com/word_tv/leng_abide.mp4
abide	http://baicizhan.qiniucdn.com/word_tv/noun_abide.mp4
abide	http://baicizhan.qiniucdn.com/word_tv/abide.mp4
accommodate	http://baicizhan.qiniucdn.com/word_tv/news_play_video_1937.mp4
```

5.Run command line `get_url_ex_url.exe word_list.txt exclude.txt` to get a text file named of `Ex_url.txt`, which contain a list of word and it's url in `word_list.txt`, but exclude the url in `exclude.txt`.eg:  
>word_list.txt 

```
accommodate	/word_tv/news_play_video_1937.mp4
abundance   /word_tv/real_abundance.mp4
accord	/word_tv/real_accord.mp4
```
>exclude.txt

```
abundance   /word_tv/real_abundance.mp4
```
>Ex_url.txt

```
accommodate	http://baicizhan.qiniucdn.com/word_tv/news_play_video_1937.mp4
accord	http://baicizhan.qiniucdn.com/word_tv/real_accord.mp4
```

6.Run command line `get_nodup_word_list.exe words_list.txt` to get the unduplicated words `from word_list.txt` and store them in `nodup_words.txt`.  

7.Run command line `Rename.exe words_url.txt` in your download directory.

8.Run command line `Copy_words.exe words_list.txt source_dir` to copy file from source directory named of `source_dir`,the file name specified by the text file named of `words_list.txt`.of course the file name and directory name will be anything you like.The destination directory will be named `words_list`.eg:  
>words_list.txt

```
abdicate
abduct
aberrant
abject
```
>source_dir contain

```
abdicate.mp4
abduct_tv.mp3
real_aberrant_tv.mp4
abject_lo
```
>destination directory contain

```
abdicate.mp4
abduct_tv.mp3
real_aberrant_tv.mp4
abject_lo
```

## There are some advance feature maybe you need   
1.Pass a fixed url arrgument followed `-f` to revise your url, default fixed url is `http://baicizhan.qiniucdn.com`, eg:`Download.exe -f http://example.com/test file1.txt file2.txt`  

2.One word maybe have more than one resource, you can format your text file like this:   
>sent_fm.txt

```
abandoned	The abandoned house looks so terrifying.	/sentence_audios_dat/f_20150606_085527_1_2.dat
abandoned	The abandoned house looks so terrifying.	/sentence_audios_dat/f_20150606_085527_1_2.dat
abandoned	The abandoned building was spooky and full of debris.	/sentence_audios_dat/example_2_32647_1359437098.dat
```
then you will get downloaded file name like this:`abandoned_The abandoned house looks so terrifying_fm.dat`    

3.If you need a subname of your download file name, you need rename your text file name to end with `sometheing_`, then the file name your downloaded will start with `xxx_sometheing.xxx`.   

4.Pass an arrgument `-d` to download directly, command is `Download.exe -d file1.txt file2.txt`, your text file maybe like this:  
>direct_down_test.txt

```
Antarctic	http://baicizhan.qiniucdn.com/word_tv/real_antarctic.mp4
Catholic	http://baicizhan.qiniucdn.com/word_tv/real_catholic.mp4
Easter	http://baicizhan.qiniucdn.com/word_tv/animate_easter.mp4
```

5.If your text file named `te_fm.txt` and some file download failed, you will get a file named `Error_te_fm.txt`, then you can run command line `Download.exe -d Error_te_fm.txt` to download it.  

6.Of course it can auto recognize this pattern text file, command line is `Download.exe test.txt`   
> test.txt

```
yeah	"Are you happy?" "YEAH, I AM!"	/cropped_images/20120507_04_07_58_919.jpg
Mr.	Mr. Smith is a stylish man.	/cropped_images/14035_20130608_03_18_32_655.jpg
Communist	Marx and Engels were two of the first Communists	http://baicizhan.qiniucdn.com/cropped_images/20121022_03_07_47_625.jpg
Earth Hour	Do you want to take part in “Earth Hour this time around?	http://baicizhan.qiniucdn.com/cropped_images/20110326_08_56_17_188.jpg
```

7.If you want to auto shutdown your computer when download completed, you need pass `-S` at your command line, eg:`Download.exe file1.txt file2.txt -S`. If you need cancle the pre-set of auto shutdown, you should input `n/N` according to the promote. If you want to pass another arrgument at the meantime, just pass it, eg:`Download_1.2.exe -dfS http://example.com file1.txt file2.txt`.

8.If you like,you can store your url in text file like this:  
>test.txt

```
abbey	The abbey was the largest building on the island. 	http://baicizhan.qiniucdn.com/sentence_audios_dat/example_2_11196_1332517301.dat
windmill	/word_audios_dat/windmill.dat
http://baicizhan.qiniucdn.com/word_tv/real_egyptian.mp4
Mr.	Mr. Smith is a stylish man.	/cropped_images/14035_20130608_03_18_32_655.jpg
```
Just run command `Download1.1.exe test.txt`, everything will work well(only supported after version 1.1).  

9.If you don't like the Download.exe to rename your file, just pass the arrgument `-n`, eg:`Download.exe -nS file.exe`, only supported after version 1.2.  

## Feature  
* **Store file to the directory named of their text file name**
* **Support phrase to specify file name**
* **Support recovery broken download**
* **Rename the name of download file based on text file name**
* **Show total download progress bar**
* **Output the list of failed download**
* **Auto jump over the files of complete downloaded**
* **Support revise the url by pass an arrgument**
* **Auto jum over the url of duplicate**
* **Support pass multiple text file which comtain specified pattern url**
* **Auto shutdown your pc when download completed**
* **Support mixed url file to download**

## To-Do  
* auto scan some resource to download
* multi-thread download


