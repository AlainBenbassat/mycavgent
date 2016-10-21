<?php

function mijncavaria_organizations_page() {
  civicrm_initialize();

  // get the contact details of the current drupal user
  try {
    $currentContact = new MyCavariaIndividual();
  }
  catch (Exception $e) {
    // user has no civicrm contact, exit
    return $e->getMessage();
  }

  $html = '<p>geen organisaties gevonden</p>';

  // show the list of organizations (if applicable)
  if (count($currentContact->organizations) > 0) {
    $html = '<h2>Uw organisaties</h2>';

    foreach ($currentContact->organizations as $organization) {
      $html .= '<div class="myCavariaBlock">';

      $html .= '<p>';
      $html .= "{$organization->name}<br>";
      $html .= "{$organization->street}<br>";
      if ($organization->addressLine1) {
        $html .= "{$organization->addressLine1}<br>";
      }
      if ($organization->addressLine2) {
        $html .= "{$organization->addressLine2}<br>";
      }
      $html .= "{$organization->postalCode} {$organization->city}<br>";
      $html .= '</p>';

      $urlParameters = array(
        'query' => array(
          'a' => $organization->id,
          'b' => $organization->hash,
        ),
      );
      $url = url('mijncavaria_wijzigorganisatie', $urlParameters);
      $html .= "<p><a href=\"$url\">wijzig</a></p>";

      $html .= '</div>';
    }
  }
  else {
    $html = '';
  }

  return $html;
}
