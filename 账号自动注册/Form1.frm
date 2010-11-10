VERSION 5.00
Object = "{EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B}#1.1#0"; "shdocvw.dll"
Begin VB.Form Form1 
   AutoRedraw      =   -1  'True
   Caption         =   "天龙--自动注册"
   ClientHeight    =   11340
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   17910
   DrawStyle       =   6  'Inside Solid
   LinkTopic       =   "Form1"
   ScaleHeight     =   567
   ScaleMode       =   2  'Point
   ScaleWidth      =   895.5
   StartUpPosition =   3  '窗口缺省
   WindowState     =   2  'Maximized
   Begin VB.CommandButton Command5 
      Caption         =   "将账号填入控制端数据库"
      Height          =   495
      Left            =   15720
      TabIndex        =   5
      Top             =   1920
      Width           =   2295
   End
   Begin VB.CommandButton Command4 
      Caption         =   "注册页面"
      Height          =   495
      Left            =   15720
      TabIndex        =   4
      Top             =   0
      Width           =   2295
   End
   Begin VB.CommandButton Command3 
      Caption         =   "mail.163.com"
      Height          =   495
      Left            =   15720
      TabIndex        =   3
      Top             =   960
      Width           =   2295
   End
   Begin VB.CommandButton Command2 
      Caption         =   "自动登录邮箱"
      Height          =   495
      Left            =   15720
      TabIndex        =   2
      Top             =   1440
      Width           =   2295
   End
   Begin VB.CommandButton Command1 
      Caption         =   "自动填写"
      Height          =   495
      Left            =   15720
      TabIndex        =   1
      Top             =   480
      Width           =   2295
   End
   Begin SHDocVwCtl.WebBrowser WebBrowser1 
      Height          =   11295
      Left            =   -5040
      TabIndex        =   0
      Top             =   -120
      Width           =   15135
      ExtentX         =   26696
      ExtentY         =   19923
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

Public conn As New ADODB.Connection
Public rs As New ADODB.Recordset
Public constr

Public connctr As New ADODB.Connection
Public rsctr As New ADODB.Recordset
Public constrctr


Dim doc As IHTMLDocument2

Dim idate As String
Dim tmp As String '账号
Dim password As String '密码
Dim modcode As String '超级密码
Dim email As String '安全邮箱
Dim securecode As String ' 安全码
Dim sn As String '真实姓名
Dim certnumber As String '身份证号
Dim question As String '密码提示问题
Dim answer As String ' 密码提示的答案

Private Sub Command1_Click()
On Error Resume Next
Set doc = WebBrowser1.Document
tmp = ""
For i = 1 To 14

If i Mod 5 = 0 Then
    tmp = tmp + "_"
Else
    Randomize
    tmp = tmp + Chr(Int(Rnd * 24 + 97))
End If
Next

password = "132456789"
modcode = "111111111"
email = "zhanghao_jihuo@163.com"
securecode = "111111111"
Randomize
question = Int(Rnd * 20)
Randomize
    
    constr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" & "UserID.mdb" & ";Persist Security Info=False"
    conn.Open constr
    sql = "select Count(*) as cou FROM UserID;"
    rs.Open sql, conn, adOpenKeyset, adLockPessimistic
    If Int(rs("cou")) > 0 Then
    
    sql = "select Name as N,NameID as NI from UserID where ID = " & Str(Int(Rnd * rs("cou")) + 1) & ";"
    rs.Close
    rs.Open sql, conn, adOpenKeyset, adLockPessimistic
    sn = rs("N")
    certnumber = rs("NI")
    rs.Close
    Rnd
    Rnd
    
    Randomize
    Id = Int(Rnd * 99) + 1
    sql = "select Name as N from UserID where ID = " & Id
    
    rs.Open sql, conn, adOpenKeyset, adLockPessimistic
    If Int(question) >= 0 And Int(question) < 8 Then
    answer = rs("N")
    End If
    If Int(question) > 15 And Int(question) < 21 Then
    answer = rs("N")
    End If
    If Int(question) > 7 And Int(question) < 16 Then
    Randomize
    answer = "1976" + "0" + Trim(Str(Int(Rnd * 8))) + Trim(Str(Int(Rnd * 2))) + Trim(Str(Int(Rnd * 7) + 1))
    End If

    End If
    rs.Close
    conn.Close
    
    
    
doc.All.Item("cn").Value = tmp


doc.All.Item("passwd").Value = password

doc.All.Item("passwdverify").Value = password

doc.All.Item("modcode").Value = modcode

doc.All.Item("modcodeverify").Value = modcode

doc.All.Item("email").Value = email

doc.All.Item("securecode").Value = securecode

doc.All.Item("question").Value = question

doc.All.Item("sn").Value = sn

doc.All.Item("certnumber").Value = certnumber

doc.All.Item("answer").Value = answer
WebBrowser1.Document.parentWindow.Scroll 0, WebBrowser1.Document.body.scrollHeight
doc.All.Item("annexcode").focus
Form1.Caption = "表单填写完成"
End Sub

Private Sub Command2_Click()
On Error Resume Next
Set doc = WebBrowser1.Document
doc.All.Item("username").Value = "zhanghao_jihuo"
doc.All.Item("password").Value = "132456789"

doc.All.Item("password").focus
SendKeys "{enter}"


End Sub

Private Sub Command3_Click()
WebBrowser1.Navigate "mail.163.com"
End Sub

Private Sub Command4_Click()
  WebBrowser1.Navigate "http://account.changyou.com/reg/register.jsp"
End Sub

Private Sub Command5_Click()
 On Error Resume Next
If Len(tmp) > 0 Then
    constrctr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" & "D:\TLBB\Bin\TL_Control.mdb" & ";Persist Security Info=False"
    connctr.Open constrctr
    sql = "select * from GameAccount"
    rsctr.Open sql, connctr, 3, 2
    rsctr.AddNew
    rsctr("username") = tmp & "@changyou.com"
    rsctr("password") = password
    rsctr("modcode") = modcode
    rsctr("email") = email

    rsctr("securecode") = securecode
    rsctr("sn") = sn
    rsctr("certnumber") = certnumber
    rsctr("question") = question
    rsctr("answer") = answer
    rsctr.Update
    rsctr.Close
    connctr.Close
    
End If
Form1.Caption = "写入数据库成功"
End Sub

Private Sub Form_Resize()
'Command1.Left = Form1.Width - Command1.Width
'Command2.Left = Form1.Width - Command2.Width
'Command3.Left = Form1.Width - Command3.Width
'Command4.Left = Form1.Width - Command4.Width

  WebBrowser1.Navigate "http://account.changyou.com/reg/register.jsp"
WebBrowser1.Top = 0
WebBrowser1.Left = 0
'WebBrowser1.Width = Form1.Width - Command1.Width
WebBrowser1.Height = Form1.Height / 20.4
End Sub
