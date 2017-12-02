%% Time-stamp: <2004-04-27 18:44:11 Boris Aronov>
%% File: polythesis.cls
%% Author: Boris Aronov
%% Date: 2004-04-27
%% 
%% Class file for Polytechnic University PhD thesis. 
%% Based on the standard LaTeX2e book style.
%% Basically just sets page style and headers and footers and
%% processes options (none of which you should change from the
%% defaults for the official version).  Not tested very much.

%% <2004-04-27 17:23:43 Boris Aronov>  Updated to new (3.2) version of
%% geometry.  Else bad things happen.  Should add option to see the
%% page layout for testing.

%% Identification

\NeedsTeXFormat{LaTeX2e} % do not need any particular format that I
                         % know of.

\ProvidesClass{polythesis}[2000/07/25 v0.010 beta Polytechnic PhD
thesis class by BA]

%% Refuse to run in compatibility mode:
\if@compatibility
  \ClassError{polythesis}{LaTeX 2.09 compatibility not supported}
    {You are trying to use polythesis.cls in LaTeX 2.09 compatibility
  mode. This will not work.}
\else
\fi


%% Preliminary declarations

% default is one-sided
\newif\ifmy@twoside
\@twosidefalse
\my@twosidefalse

\newif\if@indentfirst
\@indentfirsttrue

%% Options
\DeclareOption{twoside}{\@twosidetrue\my@twosidetrue}
%\DeclareOption{twoside}{\@twosidetrue}
\DeclareOption{indentfirst}{\@indentfirsttrue}
\DeclareOption{noindentfirst}{\@indentfirstfalse}
\DeclareOption*{%
  \PassOptionsToClass{\CurrentOption}{book}%
}

%% Loading other files

% Force one-sided books! Find the right way of doing it later!!!
\ProcessOptions\relax
\PassOptionsToClass{openany,11pt}{book}
\LoadClass{book}
\ifmy@twoside
   \@twosidetrue \message{it was TRUE after loading the class}
\else
   \@twosidefalse \message{it was FALSE after loading the class}
\fi
\RequirePackage{setspace}

%% More declarations
\if@indentfirst
   \RequirePackage{indentfirst}
\fi

\if@twoside
   \ClassWarning{polythesis}{We do not support two-sided formatting
   (yet?)}
\else
   \ClassWarning{polythesis}{We seem to be working one-sided now!}
\fi


%% Commented out--using fancyhrd

% %%%%%% Some code that depends on two-sidedness, copied out of book.cls
% %%%%%% Not clear it we need to re-run it...
% \if@twoside
%   \def\ps@headings{%
%       \let\@oddfoot\@empty\let\@evenfoot\@empty
%       \def\@evenhead{\thepage\hfil\slshape\leftmark}%
%       \def\@oddhead{{\slshape\rightmark}\hfil\thepage}%
%       \let\@mkboth\markboth
%     \def\chaptermark##1{%
%       \markboth {\MakeUppercase{%
%         \ifnum \c@secnumdepth >\m@ne
%           \if@mainmatter
%             \@chapapp\ \thechapter. \ %
%           \fi
%         \fi
%         ##1}}{}}%
%     \def\sectionmark##1{%
%       \markright {\MakeUppercase{%
%         \ifnum \c@secnumdepth >\z@
%           \thesection. \ %
%         \fi
%         ##1}}}}
% \else
%   \def\ps@headings{%
%     \let\@oddfoot\@empty
%     \def\@oddhead{{\slshape\rightmark}\hfil\thepage}%
%     \let\@mkboth\markboth
%     \def\chaptermark##1{%
%       \markright {\MakeUppercase{%
%         \ifnum \c@secnumdepth >\m@ne
%           \if@mainmatter
%             \@chapapp\ \thechapter. \ %
%           \fi
%         \fi
%         ##1}}}}
% \fi

\if@twoside
\else
  \raggedbottom
\fi

\RequirePackage{fancyhdr}
\RequirePackage{calc}
%% Updated for new version.  Might work with earlier 3.x versions, did
%% not test.
\RequirePackage{geometry}[2002/07/08]

\if@twoside
   \ClassWarning{polythesis}{Booooooo!!! Cannot (yet!) use two-sided
   with PolyThesis!!!!} 
\else
 %% Page layout, from the pink booklet
 \advance\headheight by 2pt     % prevents annoying complaints about
                                % overfull boxes 
 \geometry{
%% This shows the page layout on the first page.
%% Should make this into an option. --BA
%   showframe,
   verbose,
   letterpaper,
   includehead,
   includefoot,
%   top=1in-\headheight-\headsep, % first line of text at 1 inch from the edge 
%   bottom=1in-\footskip,         % last line of text at 1in from the edge
%   left=1.5in,                   % left margin 1in, right 3/4in
%   right=0.75in}
   top=1in-\headheight-\headsep, % first line of text at 1 inch from the edge 
   bottom=1in-\footskip,         % last line of text at 1in from the edge
   left=1.5in,                   % left margin 1in, right 3/4in
   right=1in}   
%  \topmargin 0 in
%  \textheight 9in
%  \oddsidemargin .5 in
%  \evensidemargin\oddsidemargin
%  \textwidth 6.25 in
 %% This is the style you get from \pagestyle{fancy} 
 %% \fancyhead[LO,RE]{\slshape \leftmark}
 %% \fancyfoot[C]{\thepage}

 %% We go for something simpler, we redefine the plain style so that
 %% everything acts sane later
 \pagestyle{fancy}
 \fancyhf{}
 \fancyhead[R]{\thepage}
 \renewcommand{\headrulewidth}{0pt}
 \renewcommand{\footrulewidth}{0pt}
\fi

