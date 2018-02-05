# Client01 (forensics 75)

We get a file `client01.tar.gz` with a user home directory.
We do some quick search for anything interesting.

```
> grep -ir flag .
Binary file ./.mozilla/firefox/c3a958fk.default/places.sqlite matches
Binary file ./.mozilla/firefox/c3a958fk.default/secmod.db matches
Binary file ./.cache/thunderbird/5bd7jhog.default/cache2/entries/C972AC86BA22ADBFC038B134C02101C894D0078A matches
Binary file ./.cache/mozilla/firefox/c3a958fk.default/cache2/entries/698AC159A6BCBA0D13FE6F10F1A38E498F826F33 matches
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/INBOX.msf:  (B8=imapFlags)(B9=charSetOverride)(BA=charSet)(BB=highestRecordedUID)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/INBOX.msf:  (BE=dateReceived)(BF=ProtoThreadFlags)(C0=folderName)(C1=X-GM-MSGID)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/INBOX.msf:  (D3=cleanupBodies)(D4=applyToFlaggedMessages)(D5=useServerRetention)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/INBOX.msf:  (DA=op)(DB=msgKey)(DC=opFlags)(DD=newFlags)(DE=moveDest)(DF=msgSize)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/INBOX.msf:  (88=flags)(89=priority)(8A=label)(8B=statusOfset)(8C=numLines)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/INBOX.msf:  (8D=ccList)(8E=bccList)(8F=msgThreadId)(90=threadId)(91=threadFlags)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/INBOX.msf:  (B2=sortOrder)(B3=viewFlags)(B4=viewType)(B5=sortColumns)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/INBOX.msf:    ={"threadCol":{"visible":true,"ordinal":"1"},"flaggedCol":{"visible":true,\
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/Sent.msf:  (84=references)(85=recipients)(86=date)(87=size)(88=flags)(89=priority)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/Sent.msf:  (8F=msgThreadId)(90=threadId)(91=threadFlags)(92=threadNewestMsgDate)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/Templates.msf:  (84=references)(85=recipients)(86=date)(87=size)(88=flags)(89=priority)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/Templates.msf:  (8F=msgThreadId)(90=threadId)(91=threadFlags)(92=threadNewestMsgDate)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Important.msf:  (B8=highestModSeq)(B9=imapFlags)(BA=charSetOverride)(BB=charSet)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Important.msf:  (C3=dateReceived)(C4=ProtoThreadFlags)(C5=X-GM-MSGID)(C6=X-GM-THRID)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Important.msf:  (87=size)(88=flags)(89=priority)(8A=label)(8B=statusOfset)(8C=numLines)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Important.msf:  (8D=ccList)(8E=bccList)(8F=msgThreadId)(90=threadId)(91=threadFlags)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Important.msf:  (B1=MRUTime)(B2=sortType)(B3=sortOrder)(B4=viewFlags)(B5=viewType)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Important.msf:    ={"threadCol":{"visible":true,"ordinal":"1"},"flaggedCol":{"visible":true,\
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Trash.msf:  (B8=columnStates)(B9=highestModSeq)(BA=imapFlags)(BB=charSetOverride)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Trash.msf:  (C2=gloda-dirty)(C3=ProtoThreadFlags)(C4=X-GM-MSGID)(C5=X-GM-THRID)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Trash.msf:  (D3=ns:msg:db:table:kind:ops)(D4=op)(D5=msgKey)(D6=opFlags)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Trash.msf:  (D7=newFlags)(D8=srcFolderURI)(D9=srcMsgKey)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Trash.msf:  (84=references)(85=recipients)(86=date)(87=size)(88=flags)(89=priority)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Trash.msf:  (8F=msgThreadId)(90=threadId)(91=threadFlags)(92=threadNewestMsgDate)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Trash.msf:  (B5=viewFlags)(B6=viewType)(B7=sortColumns)>
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Trash.msf:  (AA=flag)(AB
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Trash.msf:    ={"threadCol":{"visible":true,"ordinal":"1"},"flaggedCol":{"visible":true,\
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Spam.msf:  (B8=columnStates)(B9=highestModSeq)(BA=imapFlags)(BB=charSetOverride)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Spam.msf:  (88=flags)(89=priority)(8A=label)(8B=statusOfset)(8C=numLines)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Spam.msf:  (8D=ccList)(8E=bccList)(8F=msgThreadId)(90=threadId)(91=threadFlags)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Spam.msf:  (B5=viewFlags)(B6=viewType)(B7=sortColumns)>
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Spam.msf:    ={"threadCol":{"visible":true,"ordinal":"1"},"flaggedCol":{"visible":true,\
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Trash:Subject: flag
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Starred.msf:  (84=references)(85=recipients)(86=date)(87=size)(88=flags)(89=priority)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Starred.msf:  (8F=msgThreadId)(90=threadId)(91=threadFlags)(92=threadNewestMsgDate)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Starred.msf:  (B1=highestModSeq)(B2=imapFlags)(B3=charSetOverride)(B4=charSet)>
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Sent Mail.msf:  (B8=highestModSeq)(B9=imapFlags)(BA=charSetOverride)(BB=charSet)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Sent Mail.msf:  (BE=ns:msg:db:table:kind:pending)(BF=dateReceived)(C0=ProtoThreadFlags)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Sent Mail.msf:  (D0=msgKey)(D1=opFlags)(D2=newFlags)(D3=moveDest)(D4=msgSize)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Sent Mail.msf:  (88=flags)(89=priority)(8A=label)(8B=statusOfset)(8C=numLines)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Sent Mail.msf:  (8D=ccList)(8E=bccList)(8F=msgThreadId)(90=threadId)(91=threadFlags)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Sent Mail.msf:  (B1=MRUTime)(B2=sortType)(B3=sortOrder)(B4=viewFlags)(B5=viewType)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Sent Mail.msf:    ={"threadCol":{"visible":true},"attachmentCol":{"visible":true},"flaggedCo\
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Sent Mail.msf:  (DA=useServerDefaults)(DB=cleanupBodies)(DC=applyToFlaggedMessages)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Drafts.msf:  (B8=highestModSeq)(B9=imapFlags)(BA=charSetOverride)(BB=charSet)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Drafts.msf:  (84=references)(85=recipients)(86=date)(87=size)(88=flags)(89=priority)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Drafts.msf:  (8F=msgThreadId)(90=threadId)(91=threadFlags)(92=threadNewestMsgDate)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Drafts.msf:  (B1=MRUTime)(B2=sortType)(B3=sortOrder)(B4=viewFlags)(B5=viewType)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/Drafts.msf:    ={"threadCol":{"visible":true},"attachmentCol":{"visible":true},"flaggedCo\
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/All Mail.msf:  (B8=dateReceived)(B9=ProtoThreadFlags)(BA=folderName)(BB=X-GM-MSGID)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/All Mail.msf:  (C5=replyTo)(C6=sortType)(C7=sortOrder)(C8=viewFlags)(C9=viewType)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/All Mail.msf:  (86=date)(87=size)(88=flags)(89=priority)(8A=label)(8B=statusOfset)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/All Mail.msf:  (91=threadFlags)(92=threadNewestMsgDate)(93=children)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/All Mail.msf:  (B1=highestModSeq)(B2=imapFlags)(B3=charSetOverride)(B4=charSet)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/All Mail.msf:<(93=flag)>[3:^9A(^95^93)]
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].sbd/All Mail.msf:    ={"threadCol":{"visible":true,"ordinal":"1"},"flaggedCol":{"visible":true,\
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/Drafts.msf:  (84=references)(85=recipients)(86=date)(87=size)(88=flags)(89=priority)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/Drafts.msf:  (8F=msgThreadId)(90=threadId)(91=threadFlags)(92=threadNewestMsgDate)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/INBOX:Subject: flag
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].msf:  (84=references)(85=recipients)(86=date)(87=size)(88=flags)(89=priority)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].msf:  (8F=msgThreadId)(90=threadId)(91=threadFlags)(92=threadNewestMsgDate)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/[Gmail].msf:  (B8=cleanupBodies)(B9=applyToFlaggedMessages)(BA=useServerRetention)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/Archives.msf:  (84=references)(85=recipients)(86=date)(87=size)(88=flags)(89=priority)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/Archives.msf:  (8F=msgThreadId)(90=threadId)(91=threadFlags)(92=threadNewestMsgDate)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com.msf:  (84=references)(85=recipients)(86=date)(87=size)(88=flags)(89=priority)
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com.msf:  (8F=msgThreadId)(90=threadId)(91=threadFlags)(92=threadNewestMsgDate)
Binary file ./.thunderbird/5bd7jhog.default/places.sqlite matches
Binary file ./.thunderbird/5bd7jhog.default/calendar-data/local.sqlite matches
./.thunderbird/5bd7jhog.default/blocklist-addons.json:        "why": "Certain versions of this add-on contains an executable that is flagged by multiple tools as malware. Newer versions no longer use it.",
./.thunderbird/5bd7jhog.default/panacea.dat:  (8A=charset)(8B=boxFlags)(8C=hierDelim)(8D=onlineName)(8E=aclFlags)
./.thunderbird/5bd7jhog.default/panacea.dat:  (81=ns:msg:db:table:kind:folders)(82=key)(83=flags)(84=totalMsgs)
Binary file ./.thunderbird/5bd7jhog.default/kinto.sqlite matches
Binary file ./.thunderbird/5bd7jhog.default/secmod.db matches
./.thunderbird/5bd7jhog.default/Mail/Local Folders/Trash.msf:  (84=references)(85=recipients)(86=date)(87=size)(88=flags)(89=priority)
./.thunderbird/5bd7jhog.default/Mail/Local Folders/Trash.msf:  (8F=msgThreadId)(90=threadId)(91=threadFlags)(92=threadNewestMsgDate)
./.thunderbird/5bd7jhog.default/Mail/Local Folders/Trash.msf:  (B8=applyToFlaggedMessages)(B9=useServerRetention)(B2=retainBy)
./.thunderbird/5bd7jhog.default/Mail/Local Folders/Unsent Messages.msf:  (B8=applyToFlaggedMessages)(B9=useServerRetention)
./.thunderbird/5bd7jhog.default/Mail/Local Folders/Unsent Messages.msf:  (84=references)(85=recipients)(86=date)(87=size)(88=flags)(89=priority)
./.thunderbird/5bd7jhog.default/Mail/Local Folders/Unsent Messages.msf:  (8F=msgThreadId)(90=threadId)(91=threadFlags)(92=threadNewestMsgDate)
Binary file ./.thunderbird/5bd7jhog.default/global-messages-db.sqlite matches
./.xsession-errors.old:    'su', (bus_name, flags)))
./.xsession-errors:    'su', (bus_name, flags)))
```

There's clearly something interesting in that output, an mail with `flag` subject:

```
./.thunderbird/5bd7jhog.default/ImapMail/imap.gmail.com/INBOX:Subject: flag
```

We open that inbox file, look for the email and see that it contains a
[link to a file](http://www.filehosting.org/file/details/720884/Ncemd1SxbOVaOrbW/file).

We download the [file](file) open in and see what it seems like a PNG file:

```
00000010: 894e 470d 0a1a 0a00 0000 0d49 4844 5200  .NG........IHDR.
00000010: 0003 e800 0000 c804 0300 0000 89c9 d67c  ...............|
00000020: 0000 001b 504c 5445 0000 00ff ffff 5f5f  ....PLTE......__
...
```

The problem is that the magic value of the file is incorrect
we replace the first byte by a `P` and we can now see the flag:

![the flag](file.png)
