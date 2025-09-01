#!/bin/sh
# Convert some LaTeX used in parameterized labs to Markdown for integrated labs

# Usage:
#   ./latex2md.sh input.tex > output.md
# Note:
#   This script only makes a first draft of the target Markdown file.
#   Manual edits will be required,

sed -E -f - "$@" <<'SED'
  ## Zero-Argument Conversions ##

  # \_
  s/\\_/_/g

  # \dots
  s/\\dots/…/g

  # \textonehalf
  s/\\textonehalf/½/g

  ## One-Argument Conversions ##

  # double-quotes
  s/``([^']*)''/"\1"/g

  # single-quotes
  s/`([^']*)'/'\1\'/g

  # \textit{XX}
  s/\\textit\{([^}]*)\}/*\1*/g

  # \textbf{XX}
  s/\\textbf\{([^}]*)\}/**\1**/g

  # \texttt{XX}
  s/\\texttt\{([^}]*)\}/`\1`/g

  # \lstinline{XX}
  s/\\lstinline\{([^}]*)\}/`\1`/g

  # \function{XX}
  s/\\function\{([^}]*)\}/`\1`/g

  # \item XX
  s/\\item[[:space:]]+(.*)/- \1/g

  ## Two-Argument Conversions ##

  # \item[XX] YY
  s/\\item\[([^]]+)\][[:space:]]*(.*)/- **\1** \2/g

  # \textcolor{XX}{YY}
  s/\\textcolor\{([^}]*)\}\{([^}]*)\}/<font color="\1">\2<\/font>/g

  # \colorbox{XX}{YY}
  s/\\colorbox\{([^}]*)\}\{([^}]*)\}/<span style="background-color: \1;">\2<\/span>/g

  # \rubricitem{XX}{YY}
  s/\\rubricitem\{([^}]*)\}\{([^}]*)\}/- [ ] **+\1** \2/g

  ## Environment Delimiters ##

  # \begin{itemize}       →     <!-- itemize -->
  s/\\begin\{itemize\}/<!-- itemize -->/g

  # \begin{enumerate}     →     <!-- enumerate -->
  s/\\begin\{enumerate\}/<!-- enumerate -->/g

  # \begin{lstlisting}    →     ```c  (we shall assume C)
  s/\\begin\{lstlisting\}/```c/g

  # Any other \begin{XX}  →     blank line
  s/\\begin\{[^}]+\}//g

  # \end{lstlisting}      →     ```
  s/\\end\{lstlisting\}/```/g

  # Any other \end{XX}    →     blank line
  s/\\end\{[^}]+\}//g

  ## This probably needs to be last ##

  # \checkoffitem{XX}
  s/\\checkoffitem\{([^}]*)\}/- [ ] \1/g
SED
