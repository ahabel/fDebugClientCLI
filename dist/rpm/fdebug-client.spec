%define packer Andreas Habel <virus-d@fcms.de>

Name:           fcms-fdebug
Version:        0.3.2
Release:        1
Summary:        fDebug Client
Group:	        Utilities/System
License:        fpl
Vendor:		fCMS Development Team
Packager:	%packer
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-build
BuildRequires:  libxml2-devel
Source: 	fcms-fdebug.tar.gz
Provides:	fcms-fdebug-%version-%{release}

%description
fDebug Commandline Client

%prep
%setup -n %{name}

%build
cd release
make all

cd ../docs/man/
gzip -c fdebug.1 > fdebug.1.gz

%install
[ ${RPM_BUILD_ROOT} != "/" ] && rm -rf ${RPM_BUILD_ROOT}
install -m 755 -d $RPM_BUILD_ROOT/usr/bin/
install -m 755 -d $RPM_BUILD_ROOT/usr/share/man/man1/
 
# client
install -m 755 release/fdebug $RPM_BUILD_ROOT/usr/bin/fdebug
install -m 755 docs/man/fdebug.1.gz $RPM_BUILD_ROOT/usr/share/man/man1/fdebug.1.gz

%clean
[ ${RPM_BUILD_ROOT} != "/" ] && rm -rf ${RPM_BUILD_ROOT}


%files
%defattr(-,root,root,-)
/usr/bin/fdebug
/usr/share/man/man1/fdebug.1.gz
