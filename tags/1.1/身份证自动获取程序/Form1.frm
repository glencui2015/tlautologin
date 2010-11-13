VERSION 5.00
Object = "{EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B}#1.1#0"; "shdocvw.dll"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   12150
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   17745
   LinkTopic       =   "Form1"
   ScaleHeight     =   12150
   ScaleWidth      =   17745
   StartUpPosition =   3  '窗口缺省
   WindowState     =   2  'Maximized
   Begin VB.TextBox Text1 
      Height          =   11175
      Left            =   14280
      MultiLine       =   -1  'True
      TabIndex        =   2
      Text            =   "Form1.frx":0000
      Top             =   840
      Width           =   3375
   End
   Begin VB.CommandButton Command1 
      Caption         =   "获取身份证号"
      Height          =   615
      Left            =   15240
      TabIndex        =   1
      Top             =   0
      Width           =   2415
   End
   Begin SHDocVwCtl.WebBrowser WebBrowser1 
      Height          =   9855
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   13095
      ExtentX         =   23098
      ExtentY         =   17383
      ViewMode        =   0
      Offline         =   0
      Silent          =   0
      RegisterAsBrowser=   0
      RegisterAsDropTarget=   1
      AutoArrange     =   0   'False
      NoClientEdge    =   0   'False
      AlignLeft       =   0   'False
      NoWebView       =   0   'False
      HideFileNames   =   0   'False
      SingleClick     =   0   'False
      SingleSelection =   0   'False
      NoFolders       =   0   'False
      Transparent     =   0   'False
      ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
      Location        =   "http:///"
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public connctr As New ADODB.Connection
Public rsctr As New ADODB.Recordset
Public constrctr

Private Sub Command1_Click()
Dim HtmlText As String
Dim insert As Integer
Dim username As String
Dim certnumber As String
Dim inter As Integer
constrctr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" & "UserID.mdb" & ";Persist Security Info=False"
connctr.Open constrctr


HtmlText = WebBrowser1.Document.body.innerText
'Text1.Text = HtmlText
insert = 0
Text1.Text = ""
Do
    insert = insert + 1
    insert = InStr(insert, HtmlText, "姓名")
    If insert <> 0 Then
        username = Mid(HtmlText, insert + 3, 3)
     '   Text1.Text = username
        Trim (username)
        LTrim username
        
        insert = insert + 3
        insert = InStr(insert, HtmlText, "号码")
        If insert <> 0 Then
            certnumber = Mid(HtmlText, insert + 4, 18)
        End If
        insert = insert + 20
    End If
    If Len(username) <> 0 And Len(certnumber) <> 0 Then
        sql = "select count(*) as cou from UserID where NameID = " & "'" & certnumber & "'"
        rsctr.Open sql, connctr, adOpenKeyset, adLockPessimistic
        inter = Int(rsctr("cou"))
        rsctr.Close
        
        
        If inter = 0 Then
            sql = "select * from UserID"
            rsctr.Open sql, connctr, adOpenKeyset, adLockPessimistic
            rsctr.AddNew
            rsctr("Name") = username
            rsctr("NameID") = certnumber
            rsctr.Update
            rsctr.Close
        End If
       
        Text1.Text = Text1.Text + "username:" & username & "certnumber:" & certnumber & Chr(13)
    End If
    
    username = ""
    certnumber = ""
Loop While insert < Len(HtmlText) And insert <> 0
connctr.Close
End Sub

Private Sub Form_Load()
WebBrowser1.Width = Form1.Width
WebBrowser1.Height = Form1.Height - 1000
End Sub

Private Sub Form_Resize()
WebBrowser1.Navigate "http://idcard.gxsky.com/more_card.asp?city=南宁市"
End Sub
