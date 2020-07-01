using System.Collections;
using System.Collections.Generic;
using System.Threading;
using UnityEngine;
using System;

public class RefreshPlayers : MonoBehaviour
{
    private bool check = true;
    void Update()
    {
        if (check)
        {
            check = false;
            StartCoroutine(Wait());
        }
    }
    IEnumerator Wait()
    {
        ClientSend.GetRoomState();
        yield return new WaitForSeconds(3f);
        check = true;
    }
}
