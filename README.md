<h1 align="center">CrossRoad</h1>

## 프로젝트 참여자

**4인개발**
김석현, 박태호, 정현철, 허수연


## 사용프로그램
- Visual Studio 2015
- GitHub : 코드 관리 목적


## 인게임 스크린샷
<div>
<img width="800" src="https://user-images.githubusercontent.com/47206217/64910638-7794ab00-d753-11e9-9a67-2ecc15f4388e.PNG">
<img width="800" src="https://user-images.githubusercontent.com/47206217/64910639-7794ab00-d753-11e9-89a4-126509ee356f.PNG">
<img width="800" src="https://user-images.githubusercontent.com/47206217/64910640-7794ab00-d753-11e9-91e9-b679a9eef9c5.PNG">
<img width="800" src="https://user-images.githubusercontent.com/47206217/64910641-782d4180-d753-11e9-8220-d0b76c6a8545.PNG">
<img width="800" src="https://user-images.githubusercontent.com/47206217/64910642-782d4180-d753-11e9-8e54-1710bedb396c.PNG">
<img width="800" src="https://user-images.githubusercontent.com/47206217/64910644-782d4180-d753-11e9-93ad-3df060c2ef17.PNG">

</div>

## 게임 주요 코드

### 튜토리얼 대화스크립트 호출

-대화스크립트 스키마 : 스크립트 순서 번호, 이벤트 호출 번호, 캐릭터이름, 대화

~~~
    IEnumerator TutorialTextCoroutine()
    {
        /// <summary>
        /// CurrentText에서 text를 미리 캐싱해놓음
        /// </summary>
        TutoriaMainTextLayOut.gameObject.SetActive(true);
        TutorialMenualText.text = DummyText.text;
        TemporatySave.text = DummyText.text;
        SkipButton.gameObject.SetActive(true);

        if (TextNumber == 18) // 씬넘기기
        {
            SceneChange.Instance.MapSettingGameStartTutorial();
            yield return new WaitForSeconds(0.9f);
        }
        CurrentText = XMLMapSettingTutorial.Instance.GetMapSettingTutorial(TextNumber);
        if(TextNumber==23)
        {
            yield return new WaitForSeconds(0.2f);
        }
        EventProduct(CurrentText.EventNumber); // 이벤트씬 
        CharactersName.text = CurrentText.Characters; // 현 대화창 이름
        TemporatySave.text = CurrentText.MenualExplanationText;
        yield return new WaitForSeconds(0.1f); // 일부러 지연시킴 TemporatySave가 빠르게 읽지를 못하는경우가 있어서
        while (true)
        {
            TutorialMenualText.text = TutorialMenualText.text.ToString().Insert(TutorialMenualText.text.ToString().Length, TemporatySave.text[TextCount].ToString());
            yield return new WaitForSeconds(0.01f); // 일부러 지연시킴
            SoundManagement.Instance.KeyboardSound();
            yield return new WaitForSeconds(TextTime); // 텍스트 나오는 속도
            TextCount++;
            if (TemporatySave.text.ToString().Length <= TutorialMenualText.text.ToString().Length)
            {
                //Debug.Log("여기 지나나?");
                TextCount = 0; // 텍스트 카운트 리셋시켜줌
                if (CurrentText.EventNumber != 30)
                {
                    NextButton.gameObject.SetActive(true);  // 대화스크립트가 끝나면 여기서 멈춰줌
                    UI_animaiton.Instance.StartCoroutine("UI_ani");
                }
                Debug.Log("이벤트제어 변수 값 :  " + CurrentText.EventNumber);
                if (CurrentText.EventNumber == 9)
                {
                    CharactersName.GetComponent<Text>().text = "릴리";
                }

                else if (CurrentText.EventNumber == 30)
                {
                    NextButton.gameObject.SetActive(false);

                   LilyLeft.GetComponent<CharEvent>().BoxSetActiveTrue();
                   Ellisia.GetComponent<CharEvent>().BoxSetActiveTrue();
                }
                StopCoroutine("TutorialTextCoroutine"); // 대화스크립트가 끝나면 여기서 멈춰줌
                break;
            }           
        }
    }
~~~

### 타워 생성 및 저장 (맵생성과 비슷 ->생략)

~~~
    public void Create()
    {
        MonsterSummons = new List<XMLMonsterSummonData>();
        XmlDocument Document = new XmlDocument();
        XmlElement MonsterSummonListElement = Document.CreateElement("MonsterSummonList");
        Document.AppendChild(MonsterSummonListElement);
        Document.Save(Application.dataPath + filePath);
    }

    public void LoadXml()
    {
        MonsterSummons = new List<XMLMonsterSummonData>();
        XmlDocument Document = new XmlDocument();
        Document.Load(Application.dataPath + filePath);
        XmlElement MonsterSummonListElement = Document["MonsterSummonList"];

        foreach(XmlElement MonsterSummonElement in MonsterSummonListElement.ChildNodes)
        {
            XMLMonsterSummonData MonsterSummon = new XMLMonsterSummonData
            {
                iCount = System.Convert.ToInt32(MonsterSummonElement.GetAttribute("iCount")),
                fPosX = System.Convert.ToSingle(MonsterSummonElement.GetAttribute("fPosX")),
                fPosY = System.Convert.ToSingle(MonsterSummonElement.GetAttribute("fPosY")),
                InherentNumber = System.Convert.ToInt32(MonsterSummonElement.GetAttribute("InherentNumber")),
            };
            MonsterSummons.Add(MonsterSummon);
        }
    }

    public void AddXmlNode(string iCount,string InherentNumber, string fPosX, string fPosY)
    {
        MonsterSummons = new List<XMLMonsterSummonData>();
        XmlDocument Document = new XmlDocument();
        Document.Load(Application.dataPath + filePath);
        XmlElement MonsterSummonListElement = Document["MonsterSummonList"];

        XmlNode node = Document.DocumentElement;
        XmlElement childNode = Document.CreateElement("MonsterSummon");

        childNode.SetAttribute("InherentNumber", InherentNumber); 
        childNode.SetAttribute("iCount", iCount); // 문제될수도있음
        childNode.SetAttribute("fPosX", fPosX);
        childNode.SetAttribute("fPosY", fPosY);

        MonsterSummonListElement.AppendChild(childNode);

        Document.Save(Application.dataPath + filePath);
    }
~~~

### 특성 컨트롤
- 특성 체크(저장및활성화)
~~~
public class CharacteristicUsedPointValue : Singleton<CharacteristicUsedPointValue> // 특성마다 포인트가치가 다르기 때문에 따로 스크립트를 뽑은것
{                                                                                   // 어디서든 참조 가능하게 싱글톤으로 설정
    public float CUPV_CharacteristicName;       // 플레이어 특성에 대한 고유이름
    public float CUPV_CharacteristicPointValue; // 플레이어 특성에 대한 포인트 가치
    float BoolCheck;

    public GameObject Transparency;             // 투명 오브젝트
    public GameObject GoldFrame;                // 찍히면 줌
    XMLCharInfoCharacteristicData CurrentData;

    private void Start()
    {
        TransparencyLoad();
    }

    public void TransparencyLoad()
    {
        CurrentData = XMLCharInfoCharacteristic.Instance.GetCharacteristic((int)CUPV_CharacteristicName);
        if (CurrentData.Bool == 1)
        {
            Transparency.SetActive(false);
            GoldFrame.SetActive(true);
            BoolCheck = 1;
        }
        else
        {
            Transparency.SetActive(true);
            BoolCheck = 0;
        }
    }

    public void CharacteristicUsed() // 특성 사용함수
    {
        if (BoolCheck == 1)
        {
            return;
        }
        else
        {
            if (CharacteristicUIData.Instance.CharacteristicPoint >= CUPV_CharacteristicPointValue) // 특성포인트가 특성가치보다 높거나 같을경우만 실행
            {
                CharacteristicUIData.Instance.CharacteristicUsedPoint(CUPV_CharacteristicPointValue);// 플레이어가 특성포인트 사용
                CharacteristicUIData.Instance.CharacteristicPointLeave();// 플레이어가 가지고있는 최종 특성포인트 계산함수
                XMLCharInfoCharacteristic.Instance.AddXmlNode(XMLCharInfoCharacteristic.Instance.CharacteristicLength().ToString(),CUPV_CharacteristicName.ToString(), "1"); // 이름,"1"=>Bool값
                XMLCharInfoCharacteristicPoint.Instance.CreateXml();
                XMLCharInfoCharacteristic.Instance.LoadXml();
                CharacteristicUIXMLLoad.Instance.CurrentCharacteristicPointText();
                TransparencyLoad();
            }
            else
            {
                return;
            }
        }
    }
}
~~~

- 특성 적용체크함수
~~~
    public void CharacteristicActivation(int _InherentNumber)
    {
        #region 빨강색 특성, 타워 공격력 증가
        if (_InherentNumber == 0)
        {
            fTowerAttack = 1.0f;
            CurrentfTowerAttack += fTowerAttack;
        }
        else if (_InherentNumber == 1)
        {
            fTowerAttack = 2.0f;
            CurrentfTowerAttack += fTowerAttack;
        }
        else if (_InherentNumber == 2)
        {
            fTowerAttack = 4.0f;
            CurrentfTowerAttack += fTowerAttack;
        }
        else if (_InherentNumber == 3)
        {
            fTowerAttack = 8.0f;
            CurrentfTowerAttack += fTowerAttack;
            Debug.Log(CurrentfTowerAttack);
        }
        #endregion
        #region 파랑색 특성, 적 이동속도 감소
        else if (_InherentNumber == 4)
        {
            fEnemySpeed = 0.01f;
            CurrentfEnemySpeed -= fEnemySpeed;
        }
        else if (_InherentNumber == 5)
        {
            fEnemySpeed = 0.02f;
            CurrentfEnemySpeed -= fEnemySpeed;
        }
        else if (_InherentNumber == 6)
        {
            fEnemySpeed = 0.04f;
            CurrentfEnemySpeed -= fEnemySpeed;
        }
        else if (_InherentNumber == 7)
        {
            fEnemySpeed = 0.08f;
            CurrentfEnemySpeed -= fEnemySpeed;
        }
        #endregion
        #region 노랑색 특성, 타워 공격 딜레이 감소
        else if (_InherentNumber == 8)
        {
            fTowerDelay = 0.001f;
            CurrentfTowerDelay -= fTowerDelay;
        }
        else if (_InherentNumber == 9)
        {
            fTowerDelay = 0.002f;
            CurrentfTowerDelay -= fTowerDelay;
        }
        else if (_InherentNumber == 10)
        {
            fTowerDelay = 0.004f;
            CurrentfTowerDelay -= fTowerDelay;
        }
        else if (_InherentNumber == 11)
        {
            fTowerDelay = 0.008f;
            CurrentfTowerDelay -= fTowerDelay;
        }
        #endregion
        else
        {
            return;
        }
    }
~~~

### 타워 공격
- 타워사정범위 안에 가장 먼저 들어온 적 판별 하기 위한 List
~~~
    public List<EnemyMove> ObjectInRangeList = new List<EnemyMove>();
    void OnTriggerEnter(Collider col)
    {
        if (col.gameObject.tag == "Enemy")
        {
            ObjectInRangeList.Add(col.gameObject.GetComponent<EnemyMove>());

            if (NotRange == false)
            {
                StartCoroutine("DelayBullet");
                NotRange = true;
            }
        }
    }
~~~

## 인게임 동영상 주소

https://www.youtube.com/watch?v=mphLWU3Vsqk

## 게임 기획서

<img src="https://user-images.githubusercontent.com/47206217/56944074-1467fa80-6b5d-11e9-8017-cd0208ac7626.PNG" width="90%"></img>



