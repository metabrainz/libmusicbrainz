#!/bin/bash

DoIt()
{
	SRCREPO="git://github.com/metabrainz/libmusicbrainz.git"
	PUSHURL="git@github.com:metabrainz/libmusicbrainz.git"

	#Enable these 4 lines for local access only
	#rm -rf $SRCDIR/../flactag.git-local
	#git init --bare $SRCDIR/../libmusicbrainz.git-local
	#SRCREPO="/home/andy/software/libmusicbrainz.git"
	#PUSHURL="$SRCDIR/../libmusicbrainz.git-local"

	echo "Entering work directory"
	cd $WORKDIR || return 1

	echo "Cloning repository"
	git clone --quiet $SRCREPO . || return 1

	echo "Setting remote push URL"
	git remote set-url origin --push $PUSHURL || return 1

	echo "Running cmake"
	cmake . >/dev/null || return 1

	echo "Making tarball"
	make dist >/dev/null || return 1

	echo "Checking for tarball $TARBALL"
	[ -f $TARBALL ] || return 1

	echo "Copying tarball to $EXTRACTDIR"
	cp $TARBALL $EXTRACTDIR || return 1

	echo "Entering extract directory"
	cd $EXTRACTDIR || return 1

	echo "Extracting tarball"
	tar xzf $TARBALL || return 1

	echo "Building"
	cd libmusicbrainz-$VERSION || return 1
	cmake . > /dev/null || return 1
	make $MAKEARGS > /dev/null || return 1

	echo "Install test"
	mkdir "$EXTRACTDIR/install-test" | return 1
	make DESTDIR="$EXTRACTDIR/install-test" install > /dev/null || return 1

	echo "Installed binary test"
	ldd "$EXTRACTDIR/install-test/usr/local/lib/libmusicbrainz5.so" > /dev/null || return 1

	MD5=`md5sum $WORKDIR/$TARBALL | cut -d' ' -f1`
	SHA224=`sha224sum $WORKDIR/$TARBALL | cut -d' ' -f1`

	MAILTEXT="New release of libmusicbrainz $VERSION is attached:\n\nMD5: $MD5\nSHA224: $SHA224"

	if [ "$TAGANDPUSH" -eq "1" ]
	then
		echo "Tagging work repository"

		cd $WORKDIR
		git tag -s -u $KEYID -m "Tag release $VERSION" -m "MD5 checksum: $MD5" -m "SHA224 checksum: $SHA224" $TAGNAME || return 1

		COMMIT=`git show $TAGNAME | grep commit | cut -d ' ' -f 2`

		echo "Pushing new tag to origin"
		git push origin master --tags || return 1

		MAILTEXT="$MAILTEXT\nCOMMIT: $COMMIT\n"

		if ! echo -e "$MAILTEXT" | mutt -s "libmusicbrainz release" -a $TARBALL -- $KEYID
		then
			(echo -e "$MAILTEXT"; uuencode $TARBALL $TARBALL) | Mail -s "libmusicbrainz release" $KEYID
		fi

		git --no-pager show --raw $TAGNAME

		echo
	fi

	echo -e "$MAILTEXT"
	return 0
}

VALIDARGS=0
TAGANDPUSH=0

if [ "$#" -eq "2" -o "$#" -eq "3" ]
then
	VALIDARGS=1

	#rm -rf /tmp/tmp.*

	if [ "$#" -eq "3" ]
	then
		if [ "x$3" = "x--tag-and-push" ]
		then
			TAGANDPUSH=1
		else
			VALIDARGS="0"
		fi
	fi
fi

if [ "$VALIDARGS" -eq "1" ]
then
	VERSION="$1"
	KEYID="$2"

	SRCDIR=`pwd`
	TARBALL="libmusicbrainz-$VERSION.tar.gz"
	TAGNAME="test-$VERSION"

	#Comment this line out to do test pushes
	TAGNAME="release-$VERSION"

	WORKDIR=`mktemp -d`
	EXTRACTDIR=`mktemp -d`

	echo "Using directories $WORKDIR and $EXTRACTDIR"

	DoIt
	RET=$?

	if [ "$RET" -eq "1" -o "$TAGANDPUSH" -eq "1" ]
	then
		rm -rf $WORKDIR
	else
		echo "Files remain in $WORKDIR"
	fi

	rm -rf $EXTRACTDIR
else
	echo "Usage: $0 version keyid [ --tag-and-push ]"
fi
