unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, RTTIGrids, Forms, Controls, Graphics, Dialogs,
  StdCtrls, ExtCtrls, Grids, ComCtrls, ActnList, Menus, process;

type

  { TForm1 }

  TForm1 = class(TForm)
    FilesList: TListView;
    Label4: TLabel;
    MenuItem1: TMenuItem;
    MenuItem2: TMenuItem;
    PopupMenu1: TPopupMenu;
    SearchBtn: TButton;
    Button2: TButton;
    Button3: TButton;
    ExitBtn: TButton;
    Extension: TEdit;
    SearchPath: TEdit;
    Edit3: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Panel1: TPanel;
    SelectDirectoryDialog1: TSelectDirectoryDialog;
    TStatus: TLabel;
    procedure Button2Click(Sender: TObject);
    procedure MenuItem1Click(Sender: TObject);
    procedure MenuItem2Click(Sender: TObject);
    procedure SearchBtnClick(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure ExitBtnClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { private declarations }
  public
    { public declarations }
    FilesCount: Integer;
    SearchStatus: Integer;
  end;

  function NormalizePath(Path: string): string;
  function NormalizeExpr(Expr: string): string;
  procedure ClearResult();
  procedure ListFileDir(Path: string; Expr: string);
  procedure AddFileToList(SR: TSearchRec; Path: string);
  procedure SetTextStatus(Text: string);
  function FormatByteSize(const bytes: Longint): string;
  procedure CheckFile(SR: TSearchRec; Path: string);
  procedure LockInterface();
  procedure UnlockInterface();
  procedure StartSearch();
  procedure WriteEndSearchStatus();
  procedure DoProcess(Command: string);
  procedure DoOpenFile(PathToFile: string);
  procedure DoOpenFileInFinder(PathToFile: string);
  function isFileCintains(const PathToFile: string; const needle: string) : Boolean;
  function PosInFile(const PathToFile:string; const needle:string):integer;

var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.FormCreate(Sender: TObject);
begin
      Form1.SearchPath.Text:= GetUserDir();
end;


procedure TForm1.Button3Click(Sender: TObject);
begin
    SelectDirectoryDialog1.InitialDir :=   Form1.SearchPath.Text;
    if SelectDirectoryDialog1.Execute then
  begin
     Form1.SearchPath.Text := SelectDirectoryDialog1.FileName;
  end;
end;

procedure TForm1.SearchBtnClick(Sender: TObject);
begin
  StartSearch();
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
            Form1.SearchStatus := 2;
end;

procedure TForm1.MenuItem1Click(Sender: TObject);
begin
  DoOpenFile(Form1.FilesList.Selected.Caption);
end;

procedure TForm1.MenuItem2Click(Sender: TObject);
begin
      DoOpenFileInFinder(Form1.FilesList.Selected.Caption);
end;

procedure TForm1.ExitBtnClick(Sender: TObject);
begin
        Form1.Close;
end;


function NormalizePath(Path: string): string;
begin
    NormalizePath := IncludeTrailingBackslash(Path);
end;

function NormalizeExpr(Expr: string): string;
begin
    if  Length(Expr) < 1 then
    begin
      Expr := '*.*';
    end;
    NormalizeExpr := Expr;
end;

procedure ClearResult();
begin
    Form1.TStatus.Caption := '';
    Form1.FilesList.Clear();
    Form1.FilesCount := 0;
    Form1.SearchStatus := 0;
end;

procedure ListFileDir(Path: string; Expr: string);
var
  SR: TSearchRec;
begin
  Path := NormalizePath(Path);
  Expr := NormalizeExpr(Expr);
  // find files
  if FindFirst(Path + Expr, faAnyFile, SR) = 0 then
  begin
    repeat
      if (Application.Terminated Or (Form1.SearchStatus = 2)) then
      Break;
      if ( (SR.Attr and faDirectory) <> 0) then Continue;
         SetTextStatus('Search: ' + Path + SR.Name);
         CheckFile(SR, Path);
    until FindNext(SR) <> 0;
    FindClose(SR);
  end;
     // get directories list
  if FindFirst(Path + '*', faDirectory, SR) = 0 then
  begin
    repeat
      if (Application.Terminated Or (Form1.SearchStatus = 2)) then
      Break;
      if ( ( (SR.Attr and faDirectory) = 0) Or (SR.Name = '.') OR (SR.Name = '..')) then Continue;
         ListFileDir(Path + SR.Name, Expr);
    until FindNext(SR) <> 0;
    FindClose(SR);
  end;
end;

procedure AddFileToList(SR: TSearchRec; Path: string);
begin
   with Form1.FilesList.Items.Add do begin
      Caption:= Path + SR.Name;
      SubItems.Add( FormatByteSize(SR.Size) );
      SubItems.Add( FormatDateTime('dd.mm.yyyy', FileDateToDateTime(SR.Time)  ) );
      //SubItems.Add( IntToStr(SR.Time) );
   end;
end;

procedure SetTextStatus(Text: string);
begin
  Form1.TStatus.Caption := Text;
  Application.ProcessMessages;
end;

//Format file byte size
 function FormatByteSize(const bytes: Longint): string;
 const
   B = 1; //byte
   KB = 1024 * B; //kilobyte
   MB = 1024 * KB; //megabyte
   GB = 1024 * MB; //gigabyte
 begin
   if bytes > GB then
     result := FormatFloat('#.## GB', bytes / GB)
   else
     if bytes > MB then
       result := FormatFloat('#.## MB', bytes / MB)
     else
       if bytes > KB then
         result := FormatFloat('#.## KB', bytes / KB)
       else
         result := FormatFloat('#.## bytes', bytes) ;
 end;

procedure CheckFile(SR: TSearchRec; Path: string);
begin
     if ( isFileCintains(Path+SR.Name, Form1.Edit3.Text) ) then
     begin
       Form1.FilesCount := Form1.FilesCount + 1;
       AddFileToList(SR, Path);
     end;
end;

procedure LockInterface();
begin
  Form1.Extension.Enabled := False;
  Form1.SearchPath.Enabled:= False;
  Form1.Edit3.Enabled:= False;
  Form1.Button3.Enabled:= False;
  Form1.SearchBtn.Enabled:= False;
  Application.ProcessMessages;
end;

procedure UnlockInterface();
begin
  Form1.Extension.Enabled := True;
  Form1.SearchPath.Enabled:= True;
  Form1.Edit3.Enabled:= True;
  Form1.Button3.Enabled:= True;
  Form1.SearchBtn.Enabled:= True;
  Application.ProcessMessages;
end;

procedure WriteEndSearchStatus();
var
  Status: string;
begin
  Status := 'Files Found - ' + IntToStr(Form1.FilesCount) + '. Status: ';
  if (Form1.SearchStatus = 1) then
  begin
    Status := Status + 'successfully completed.';
  end
  else
  begin
      Status := Status + 'canceled (by user).';
  end;
  SetTextStatus(Status);
end;

procedure StartSearch();
begin
    ClearResult();
    Form1.SearchStatus := 1;
    LockInterface();
    ListFileDir(Form1.SearchPath.Text, Form1.Extension.Text);
    WriteEndSearchStatus();
    UnlockInterface();
end;

procedure DoProcess(Command: string);
Var
  Proc : TProcess;

Begin
  Proc := TProcess.Create(nil);
  try
    Proc.CommandLine := Command;

    PRoc.Options := Proc.Options + [poWaitOnExit];
    PRoc.Execute;
  finally
    Proc.free;
  end;
End;


procedure DoOpenFile(PathToFile: string);
Begin
    DoProcess('open -t '+PathToFile);
End;

procedure DoOpenFileInFinder(PathToFile: string);
Begin
    DoProcess('open -R '+PathToFile);
End;

function isFileCintains(const PathToFile: string; const needle: string) : Boolean;
begin
  Result := False;
  if ( (Length(needle) = 0) Or (PosInFile(PathToFile, needle) <> -1) ) then
     begin
       Result := True;
     end;

end;

//http://www.delphifaq.com/faq/delphi/strings/f86.shtml

function PosInFile(const PathToFile:string; const needle:string):integer;
var
    Buffer : array [0..1023] of char;
    BufPtr,BufEnd:integer;
    F:File;
    Index : integer;
    Increment : integer;
    c : char;

  function NextChar : char;
  begin
      if BufPtr>=BufEnd then
      begin
          BlockRead(F,Buffer,1024,BufEnd);
          BufPtr := 0;
          Application.ProcessMessages;
      end;
     Result := Buffer[BufPtr];
     Inc(BufPtr);
    end;

begin
    Result := -1;
    AssignFile(F,PathToFile);

    Reset(F,1);


    BufPtr:=0;
    BufEnd:=0;
    Index := 0;
    Increment := 1;
    repeat
        c:=NextChar;
        if c=needle[Increment] then
            Inc(Increment)
        else
        begin
            Inc(Index,Increment);
            Increment := 1;
         end;
        if Increment=(Length(needle)+1) then
        begin
            Result := Index;
            break;
        end;
    until BufEnd = 0;
    CloseFile(F);
end;

end.

