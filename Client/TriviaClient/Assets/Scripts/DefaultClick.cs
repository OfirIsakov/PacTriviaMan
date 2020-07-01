using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class DefaultClick : MonoBehaviour
{
    private EventSystem eventSystem;
    void Start()
    {
        eventSystem = GetComponent<EventSystem>();
    }

    void Update()
    {
        if (eventSystem != null)
        {
            if (eventSystem.currentSelectedGameObject == null)
            {
                UIManager.instance.currentRoom = null;
                UIManager.instance.SetPlayersInRoom(new string[0]);
            } 
        }
    }
}
