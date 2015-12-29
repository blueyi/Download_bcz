# A batch download program based on wget  
# Main feature: This program will download all resource file from an text file on the basis of what pattern of url line the text file contain.This program only used to technical communication, so don't used in any illegal field.  

# How to use it  
1. Get the file name and url you want to download, and store them in an text file, one per row.eg:  
>word_test.txt

```
hold on	/word_audios_dat/hold on.dat
hold on	/word_audios_dat/hold on.dat
learn (know) sth. by heart	/word_audios_dat/learn _know_ sth_ by heart.dat
```
your downloaded file stored will be `hold on_test.dat`  
2. Run Download.exe test1.txt start download, when the download has completed, you will find a directory named of `word_test`.  

# There are some advance feature maybe you need   
1. Pass a fixed url arrgument followed `-f`, default fixed url is `http://baicizhan.qiniucdn.com`, eg:`Download.exe -f http://example.com/test`  
2. One word maybe have more than one resource, you can formate your text file like this:  
>sent_fm.txt

```
abandoned	The abandoned house looks so terrifying.	/sentence_audios_dat/f_20150606_085527_1_2.dat
abandoned	The abandoned house looks so terrifying.	/sentence_audios_dat/f_20150606_085527_1_2.dat
abandoned	The abandoned building was spooky and full of debris.	/sentence_audios_dat/example_2_32647_1359437098.dat
```
then you will get downloaded file name like this:`abandoned_The abandoned house looks so terrifying_fm.dat`  
3. If you need a subname of your download file name, you need rename your text file name to end with `_sometheing`. 


# Feature  
* **Store file to the directory named of their text file name**
* **Support phrase**
* **Support recovery broken download**
* **Rename the name of download file based on text file name**
* **Show total download progress bar**
* **Output the list of failed download**
* **Auto jump over the files of complete downloaded**
* **Support revise the url by pass an arrgument**
* **Auto jum over the url of duplicate**
* **Support pass multiple text file which comtain specified pattern url**

# To-Do  
* auto scan some resource to download
* multi-thread download


